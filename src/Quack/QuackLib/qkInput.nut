// - -------------------------------------------------------------------------------------------------------------- - //
const COS0125 = 0.92387953251128675613; // cos(0.125*PI), i.e. 22.5 degrees //
const COS025 = 0.7071067811865475244;   // cos(0.25*PI), i.e. 45 degrees //
// - -------------------------------------------------------------------------------------------------------------- - //
const QK_STICK_FAST = 1.0;				// What Fast Speed is (for reference, not actually used) //
const QK_STICK_SLOW = 0.25;				// What Slow Speed is //
// - -------------------------------------------------------------------------------------------------------------- - //
const QK_STICK_DEADZONE = 0.1;			// Analog Stick threshold before any inputs are recieved //
const QK_STICK_FASTZONE = 0.7;			// Analog Stick threshold before we cross in to the Fast Speed Zone. //
										// Everything Else is the Slow Zone //
// - -------------------------------------------------------------------------------------------------------------- - //
const QK_STICK_ZONE = 0.4;				// Constant between both the Fast and Slow zone. //
										// Works on Magnitude, MagnitudeSquared, and individual axis. //
// - -------------------------------------------------------------------------------------------------------------- - //
// Convert a vec2 Stick in to a bit number //
function StickToBit( Stick ) {
	local Bit = 0;
	
	if ( Stick.y < -QK_STICK_ZONE )
		Bit = 6;
	else if ( Stick.y > QK_STICK_ZONE )
		Bit = 3;
	else if ( Stick.y < 0 )
		Bit = 12;
	else if ( Stick.y > 0 )
		Bit = 9;
//	else
//		Bit += 0;

	if ( Stick.x < -QK_STICK_ZONE )
		Bit += 1;
	else if ( Stick.x > QK_STICK_ZONE )
		Bit += 2;
	else if ( Bit == 0 ) {
		if ( Stick.x < 0 )
			Bit += 0 + 15;
		else if ( Stick.x > 0 )
			Bit += 1 + 15;
	}
	else if ( Stick.x < 0 )
		Bit += 1;
	else if ( Stick.x > 0 )
		Bit += 2;
//	else
//		Bit = 0;

	return Bit;	
}
// - -------------------------------------------------------------------------------------------------------------- - //
local _BitToStickVectors = [
	// Fast Zone - Middle //
	vec2(0,0),
	vec2(-1,0),
	vec2(1,0),
	// Fast Zone - Top //
	vec2(0,1),
	vec2(-COS025,COS025),
	vec2(COS025,COS025),
	// Fast Zone - Bottom //
	vec2(0,-1),
	vec2(-COS025,-COS025),
	vec2(COS025,-COS025),

	// Slow Zone - Top //
	vec2(0,1)*QK_STICK_SLOW,
	vec2(-COS025,COS025)*QK_STICK_SLOW,
	vec2(COS025,COS025)*QK_STICK_SLOW,
	// Slow Zone - Bottom //
	vec2(0,-1)*QK_STICK_SLOW,
	vec2(-COS025,-COS025)*QK_STICK_SLOW,
	vec2(COS025,-COS025)*QK_STICK_SLOW,
	// Slow Zone - Middle //
	vec2(-1,0)*QK_STICK_SLOW,
	vec2(1,0)*QK_STICK_SLOW,
];
// - -------------------------------------------------------------------------------------------------------------- - //
// Back the other way, convert a Bit in to an equivalent vec2 //
function BitToStick( Bit ) {
	return _BitToStickVectors[Bit];
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
class qkPad {
	Index = 0;
	InputFunc = null;
	Current = null;
	Old = null;
	
	LStick = null;
	RStick = null;
	
	// 4 way aligned Rigid Stick (Axis Aligned) //
	LStick4Way = null;
	RStick4Way = null;
	// 8 way aligned Rigid Stick (Diagonals too) //
	LStick8Way = null;
	RStick8Way = null;
	// Heavy Sticks. Diagonals always present. //
	LStickHeavy = null;
	RStickHeavy = null;
	
	// Newly Pressed directions on the Sticks //
	LStickPressed = null;
	RStickPressed = null;
	// Age of each Stick Press // 
	LStickAge = null;
	RStickAge = null;

	// Age of each button push //
	ButtonAge = null;
	
	constructor( _Index, _InputFunc ) {
		Index = _Index;
		InputFunc = _InputFunc;
		Current = InputFunc( Index );

		ButtonAge = array(12);
		for ( local idx = 0; idx < 12; idx++ ) {
			ButtonAge[idx] = 0;
		}
	
		LStickAge = array(8+8+1);
		RStickAge = array(8+8+1);
		for ( local idx = 0; idx < LStickAge.len(); idx++ ) {
			LStickAge[idx] = 0;
			RStickAge[idx] = 0;
		}

		// Because code in Update requires the 8-way's to exist //
		LStick8Way = vec2(0,0);
		RStick8Way = vec2(0,0);
		
		Update();
	}
	
	function _get( _Index ) {
		if ( _Index == "Button" ) {
			return Current.Button;
		}
		else if ( _Index == "Pressed" ) {
			return (Current.Button ^ Old.Button) & Current.Button;
		}
		else if ( _Index == "Released" ) {
			return (Current.Button ^ Old.Button) & Old.Button;
		}
		else if ( _Index == "Changed" ) {
			return (Current.Button ^ Old.Button);
		}
		throw null;
	}
	
	function _typeof() {
		return "qkPad";
	}
	function _tostring() {
		return "LStick: " + LStick + "  RStick: " + RStick + "  Button: " + Button + " (" + Pressed + "," + Released + ")";
	}
	
	function Update() {
		Old = Current;
		Current = InputFunc(Index);

		// We throw away the originals, so lets take a copy (reference) to them //
		local OldLStick8Way = LStick8Way; 
		local OldRStick8Way = RStick8Way;

		// Ages //
		for ( local idx = 0; idx < LStickAge.len(); idx++ ) {
			LStickAge[idx]++;
			RStickAge[idx]++;
		}
		
		// Aww. Can't switch this to a foreach, because it's not only reading but writing //
				
		local LStickMag = Current.LStick.magnitude();
		if ( LStickMag < QK_STICK_DEADZONE ) { // Handles division by zero case //
			LStick = vec2(0,0);
			LStick4Way = vec2(0,0);
			LStick8Way = vec2(0,0);
			LStickHeavy = vec2(0,0);
		}
		else {			
			// Calculate 4 Way //
			local LStickAbs = 0;
			if ( Current.LStick.x.abs() > Current.LStick.y.abs() ) {
				LStick4Way = vec2(Current.LStick.x/Current.LStick.x.abs(),0);
				LStickAbs = (Current.LStick.x / LStickMag).abs();
			}
			else {
				LStick4Way = vec2(0,Current.LStick.y/Current.LStick.y.abs());
				LStickAbs = (Current.LStick.y / LStickMag).abs();
			}
			
			// Calculate 8 Way //
			if ( LStickAbs < COS0125 ) { // cos(0.125*pi) -- i.e. 22.5 degrees //
				// Diagonal //
				LStick8Way = vec2(Current.LStick.x/Current.LStick.x.abs(),Current.LStick.y/Current.LStick.y.abs());
				LStick8Way *= COS025; // cos(0.25*pi) -- i.e. 45 degrees //
			}
			else {
				// Axis //
				LStick8Way = clone LStick4Way;
			}
			
			// Calculate Heavy Stick //
			LStickHeavy = vec2( Current.LStick.x.normal(), Current.LStick.y.normal() );
//			if ( (LStickHeavy.x != 0) && LStickHeavy.y != 0 ) {
//				LStickHeavy *= COS025; // cos(0.25*pi) -- i.e. 45 degrees //
//			}
			
			// Fast and Slow speed //
			if ( LStickMag < QK_STICK_FASTZONE ) {
				LStick = Current.LStick / LStickMag;
				LStick *= QK_STICK_SLOW;
				LStick4Way *= QK_STICK_SLOW;
				LStick8Way *= QK_STICK_SLOW;
				LStickHeavy *= QK_STICK_SLOW;
			}
			else {
				LStick = Current.LStick / LStickMag;
			}
		}
		// Outside, so we can detect Released states too //
		if ( (LStick8Way.x == OldLStick8Way.x) && (LStick8Way.y == OldLStick8Way.y) ) {
			// None Pressed //
			LStickPressed = vec2(0,0);
		}
		else {
			// Something was Pressed! //
			LStickPressed = LStick8Way; // NOTE: BE CAREFUL! NOT A CLONE! //

			local PadIndex = 1; //Index; //
			local Amount = 200;
			if ( LStickMag > QK_STICK_FASTZONE )
				Amount = 1600;
			else if ( LStickMag > 0 )
				Amount = 400;
			qkInputPadPulse(PadIndex,0,Amount);
			
			// NOTE: Detect Gestures Here (Double Tap, at least) //
			
			LStickAge[ StickToBit(LStick8Way) ] = 0;
		}
		

		local RStickMag = Current.RStick.magnitude();
		if ( RStickMag < QK_STICK_DEADZONE ) { // Handles division by zero case //
			RStick = vec2(0,0);
			RStick4Way = vec2(0,0);
			RStick8Way = vec2(0,0);
			RStickHeavy = vec2(0,0);
		}
		else {			
			// Calculate 4 Way //
			local RStickAbs = 0;
			if ( Current.RStick.x.abs() > Current.RStick.y.abs() ) {
				RStick4Way = vec2(Current.RStick.x/Current.RStick.x.abs(),0);
				RStickAbs = (Current.RStick.x / RStickMag).abs();
			}
			else {
				RStick4Way = vec2(0,Current.RStick.y/Current.RStick.y.abs());
				RStickAbs = (Current.RStick.y / RStickMag).abs();
			}

			// Calculate 8 Way //
			if ( RStickAbs < COS0125 ) { // cos(0.125*pi) -- i.e. 22.5 degrees //
				// Diagonal //
				RStick8Way = vec2(Current.RStick.x/Current.RStick.x.abs(),Current.RStick.y/Current.RStick.y.abs());
				RStick8Way *= COS025; // cos(0.25*pi) -- i.e. 45 degrees //
			}
			else {
				// Axis //
				RStick8Way = clone RStick4Way;
			}

			// Calculate Heavy Stick //
			RStickHeavy = vec2( Current.RStick.x.normal(), Current.RStick.y.normal() );
//			if ( (RStickHeavy.x != 0) && RStickHeavy.y != 0 ) {
//				RStickHeavy *= COS025; // cos(0.25*pi) -- i.e. 45 degrees //
//			}

			// Fast and Slow speed //
			if ( RStickMag < QK_STICK_FASTZONE ) {
				RStick = Current.RStick / RStickMag;
				RStick *= QK_STICK_SLOW;
				RStick4Way *= QK_STICK_SLOW;
				RStick8Way *= QK_STICK_SLOW;
				RStickHeavy *= QK_STICK_SLOW;
			}
			else {
				RStick = Current.RStick / RStickMag;
			}
		}
		// Outside, so we can detect Released states too //
		if ( (RStick8Way.x == OldRStick8Way.x) && (RStick8Way.y == OldRStick8Way.y) ) {
			// None Pressed //
			RStickPressed = vec2(0,0);
		}
		else {
			// Something was Pressed! //
			RStickPressed = RStick8Way; // NOTE: BE CAREFUL! NOT A CLONE! //
			
			local PadIndex = 1; //Index; //
			local Amount = 200;
			if ( RStickMag > QK_STICK_FASTZONE )
				Amount = 1600;
			else if ( RStickMag > 0 )
				Amount = 400;
			qkInputPadPulse(PadIndex,1,Amount);
			
			// NOTE: Detect Gestures Here (Double Tap, at least) //
			
			RStickAge[ StickToBit(RStick8Way) ] = 0;
		}
		
		// We want to increment here, because it makes the math later easier //
		local ButtonState = Pressed;//Changed;
		for ( local idx = 0; idx < 12; idx++ ) {
			if ( ButtonState & (1<<idx) )
				ButtonAge[idx] = 0;
			else
				ButtonAge[idx]++;
		}
		
		// idx to bit = (1<<idx)
		// bit to idx = log2(bit) or log(bit)/log(2)
		//   or the "bsr" instruction (x86), 
		
		// http://graphics.stanford.edu/~seander/bithacks.html#IntegerLog
		
		// Or the "bsr" instruction (x86), other wise some sort of ffs intrinsic
		// http://en.wikipedia.org/wiki/Find_first_set
	}
};
// - -------------------------------------------------------------------------------------------------------------- - //
function qkPadGet( Index ) {
	return qkPad(Index,qkInputPadGet);
}
// - -------------------------------------------------------------------------------------------------------------- - //

// - -------------------------------------------------------------------------------------------------------------- - //
function qkInputMasterPadGet( Index /* Ignored */ ) {
	local Pads = [];
	for ( local idx = 0; idx < 4; idx++ ) {
		Pads.push( qkInputPadGet(idx) );
	}
	
	local Ret = {};
	
	Ret.Connected <- true;
	
	Ret.LStick <- clone Pads[0].LStick;
	for ( local idx = 1; idx < Pads.len(); idx++ ) {
		if ( Ret.LStick.magnitude() < QK_STICK_DEADZONE )
			Ret.LStick = clone Pads[idx].LStick;
		else
			break;
	}

	Ret.RStick <- clone Pads[0].RStick;
	for ( local idx = 1; idx < Pads.len(); idx++ ) {
		if ( Ret.RStick.magnitude() < QK_STICK_DEADZONE )
			Ret.RStick = clone Pads[idx].RStick;
		else
			break;
	}
	
	Ret.Button <- Pads[0].Button;
	for ( local idx = 1; idx < Pads.len(); idx++ ) {
		Ret.Button = Ret.Button | Pads[idx].Button;
	}
	
	return Ret;
}
// - -------------------------------------------------------------------------------------------------------------- - //
function qkMasterPadGet() {
	return qkPad(0,qkInputMasterPadGet);
}
// - -------------------------------------------------------------------------------------------------------------- - //
