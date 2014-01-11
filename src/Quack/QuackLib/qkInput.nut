// - -------------------------------------------------------------------------------------------------------------- - //
class qkPad {
	Index = 0;
	Current = null;
	Old = null;
	
	LStick = null;
	RStick = null;
	
	constructor( _Index ) {
		Index = _Index;
		Current = qkInputPadGet( Index );
		Update();
	}
	
	function _get( _Index ) {
//		if ( _Index == "LStick" ) {
//			return Current.LStick;
//		}
//		else if ( _Index == "RStick" ) {
//			return Current.RStick;
//		}
//		else 
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
		Current = qkInputPadGet(Index);
		
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
	return qkPad(Index);
}
// - -------------------------------------------------------------------------------------------------------------- - //
