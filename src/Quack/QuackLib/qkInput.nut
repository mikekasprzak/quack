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
		
		local LStickMag = Current.LStick.magnitude();
		if ( LStickMag < 0.1 ) { // Handles division by zero case //
			LStick = vec2(0,0);
			LStick4Way = vec2(0,0);
			LStick8Way = vec2(0,0);
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
			if ( LStickAbs < 0.92387953251128675613 ) { // cos(0.125*pi) -- i.e. 22.5 degrees //
				// Diagonal //
				LStick8Way = vec2(Current.LStick.x/Current.LStick.x.abs(),Current.LStick.y/Current.LStick.y.abs());
				LStick8Way *= 0.7071067811865475244; // cos(0.25*pi) -- i.e. 45 degrees //
			}
			else {
				// Axis //
				LStick8Way = clone LStick4Way;
			}
			
			// Fast and Slow speed //
			if ( LStickMag < 0.7 ) {
				LStick = Current.LStick / LStickMag;
				LStick *= 0.25;
				LStick4Way *= 0.25;
				LStick8Way *= 0.25;
			}
			else {
				LStick = Current.LStick / LStickMag;
			}
		}
		

		local RStickMag = Current.RStick.magnitude();
		if ( RStickMag < 0.1 ) { // Handles division by zero case //
			RStick = vec2(0,0);
			RStick4Way = vec2(0,0);
			RStick8Way = vec2(0,0);
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
			if ( RStickAbs < 0.92387953251128675613 ) { // cos(0.125*pi) -- i.e. 22.5 degrees //
				// Diagonal //
				RStick8Way = vec2(Current.RStick.x/Current.RStick.x.abs(),Current.RStick.y/Current.RStick.y.abs());
				RStick8Way *= 0.7071067811865475244; // cos(0.25*pi) -- i.e. 45 degrees //
			}
			else {
				// Axis //
				RStick8Way = clone RStick4Way;
			}

			// Fast and Slow speed //
			if ( RStickMag < 0.7 ) {
				RStick = Current.RStick / RStickMag;
				RStick *= 0.25;
				RStick4Way *= 0.25;
				RStick8Way *= 0.25;
			}
			else {
				RStick = Current.RStick / RStickMag;
			}
		}
		
		// We want to increment here, because it makes the math later easier //
		local ButtonState = Changed;
		for ( local idx = 0; idx < 12; idx++ ) {
			if ( ButtonState & (1<<idx) )
				ButtonAge[idx] = 0;
			else
				ButtonAge[idx]++;
		}
		
		// idx to bit = (1<<idx)
		// bit to idx = ??
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
		if ( Ret.LStick.magnitude() < 0.1 )
			Ret.LStick = clone Pads[idx].LStick;
		else
			break;
	}

	Ret.RStick <- clone Pads[0].RStick;
	for ( local idx = 1; idx < Pads.len(); idx++ ) {
		if ( Ret.RStick.magnitude() < 0.1 )
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
