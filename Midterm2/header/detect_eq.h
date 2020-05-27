//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i

static int eq_time; // check for earthquake time
/*complete the state machine */
#define eq (~PINA & 0xF8)
void Detect_EQ()
{
    switch(detect_eq_state)
    {
        case DEQInit:
            //init variable(s) here.
	    
            detect_eq_state = no_eq;
	    break;
	case no_eq:
		eq_time = 0;
		if(eq == 0){
			detect_eq_state = no_eq;
			detect_eq = 0;
		}else{
			detect_eq_state = yes_eq;
			detect_eq = 0x02;
		}
		break;
	case yes_eq:
		if(eq == 0){
			if(eq_time < 10){
				eq_time ++;
				detect_eq_state = yes_eq;
			}else{
				detect_eq = 0x00;
				detect_eq_state = no_eq;
			}
		}else{
			detect_eq_state = yes_eq;
			eq_time = 0;
		}
		break;
        default:
            detect_eq_state = DEQInit;
            break;
    }
    switch(detect_eq_state)
    {
        case DEQInit:
            break;
        default:
            break;
    }
}
