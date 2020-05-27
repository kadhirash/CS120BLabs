
//define local variable(s) here.  Use static keyword to keep local, e.g:
//   static int i;  // defines a local int named i
/*complete the state machine*/
static int p_timer;

void Ping()
{
    switch(ping_state)
    {
        case PInit:
		ping_state = H;
		p_timer = 0;
            break;
	case H:
		ping_output = 0x01;
		ping_state = L;
		break;
	case L:
		ping_output = 0x00;
		if(p_timer < 0x09){
			ping_state = L;
			p_timer += 1;
		}else{
			ping_state = H;
			p_timer = 0;
		}
		break;
        default:
            ping_state = PInit;
            break;
    }
    switch(ping_state)
    {
        case PInit:
            break;
        default:
            break;
    }
}
