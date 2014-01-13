// - -------------------------------------------------------------------------------------------------------------- - //
const COS0125 = 0.92387953251128675613; // cos(0.125*PI), i.e. 22.5 degrees //
const COS025 = 0.7071067811865475244;   // cos(0.25*PI), i.e. 45 degrees //
// - -------------------------------------------------------------------------------------------------------------- - //
const QK_PAD_STICK_FAST = 1.0;			// What Fast Speed is (for reference, not actually used) //
const QK_PAD_STICK_SLOW = 0.25;			// What Slow Speed is //
// - -------------------------------------------------------------------------------------------------------------- - //
const QK_PAD_STICK_DEADZONE = 0.1;		// Analog Stick threshold before any inputs are recieved //
const QK_PAD_STICK_FASTZONE = 0.7;		// Analog Stick threshold before we cross in to the Fast Speed Zone. //
										// Everything Else is the Slow Zone //
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
		
		// Aww. Can't switch this to a foreach, because it's not only reading but writing //
				
		local LStickMag = Current.LStick.magnitude();
		if ( LStickMag < QK_PAD_STICK_DEADZONE ) { // Handles division by zero case //
			LStick = vec2(0,0);
			LStick4Way = vec2(0,0);
			LStick8Way = vec2(0,0);
			LStickHeavy = vec2(0,0);
			LStickPressed = vec2(0,0);
		}
		else {
			local OldLStick8Way = LStick8Way; // Throwing away original here anyway //
			
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
			if ( LStickMag < QK_PAD_STICK_FASTZONE ) {
				LStick = Current.LStick / LStickMag;
				LStick *= QK_PAD_STICK_SLOW;
				LStick4Way *= QK_PAD_STICK_SLOW;
				LStick8Way *= QK_PAD_STICK_SLOW;
				LStickHeavy *= QK_PAD_STICK_SLOW;
			}
			else {
				LStick = Current.LStick / LStickMag;
			}
			
			// Newly Pressed Stick States //
			if ( (LStick8Way.x == OldLStick8Way.x) && (LStick8Way.y == OldLStick8Way.y) ) {
				LStickPressed = vec2(0,0);
			}
			else {
				LStickPressed = clone LStick8Way; // May not need a clone //				
			}
		}
		

		local RStickMag = Current.RStick.magnitude();
		if ( RStickMag < QK_PAD_STICK_DEADZONE ) { // Handles division by zero case //
			RStick = vec2(0,0);
			RStick4Way = vec2(0,0);
			RStick8Way = vec2(0,0);
			RStickHeavy = vec2(0,0);
			RStickPressed = vec2(0,0);
		}
		else {
			local OldRStick8Way = RStick8Way; // Throwing away original here anyway //
			
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
			if ( RStickMag < QK_PAD_STICK_FASTZONE ) {
				RStick = Current.RStick / RStickMag;
				RStick *= QK_PAD_STICK_SLOW;
				RStick4Way *= QK_PAD_STICK_SLOW;
				RStick8Way *= QK_PAD_STICK_SLOW;
				RStickHeavy *= QK_PAD_STICK_SLOW;
			}
			else {
				RStick = Current.RStick / RStickMag;
			}
			
			// Newly Pressed Stick States //
			if ( (RStick8Way.x == OldRStick8Way.x) && (RStick8Way.y == OldRStick8Way.y) ) {
				RStickPressed = vec2(0,0);
			}
			else {
				RStickPressed = clone RStick8Way; // May not need a clone //
			}
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
		if ( Ret.LStick.magnitude() < QK_PAD_STICK_DEADZONE )
			Ret.LStick = clone Pads[idx].LStick;
		else
			break;
	}

	Ret.RStick <- clone Pads[0].RStick;
	for ( local idx = 1; idx < Pads.len(); idx++ ) {
		if ( Ret.RStick.magnitude() < QK_PAD_STICK_DEADZONE )
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
