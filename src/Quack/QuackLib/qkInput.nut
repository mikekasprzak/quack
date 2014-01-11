// - -------------------------------------------------------------------------------------------------------------- - //
class qkPad {
	Index = 0;
	InputFunc = null;
	Current = null;
	Old = null;
	
	LStick = null;
	RStick = null;
	
	constructor( _Index, _InputFunc ) {
		Index = _Index;
		InputFunc = _InputFunc;
		Current = InputFunc( Index );
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
		
		LStick = clone Current.LStick;
		RStick = clone Current.RStick;
		
		local LStickMag = LStick.magnitude();
		if ( LStickMag < 0.1 ) { // Handles division by zero case //
			LStick = vec2(0,0);
		}
		else if ( LStickMag < 0.5 ) {
			LStick /= LStickMag;
			LStick *= 0.25;
		}
		else {
			LStick /= LStickMag;
		}

		local RStickMag = RStick.magnitude();
		if ( RStickMag < 0.1 ) { // Handles division by zero case //
			RStick = vec2(0,0);
		}
		else if ( RStickMag < 0.5 ) {
			RStick /= RStickMag;
			RStick *= 0.25;
		}
		else {
			RStick /= RStickMag;
		}
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
