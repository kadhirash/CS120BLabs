void tick() {
  switch(state) {
    case START:
    state = LIGHT_1;
    break;
    case LIGHT_1:
    if (button) {
      state = PAUSE;
    } else {
    state = LIGHT_2;
  }
// }
    break;
    case LIGHT_2:
    if (button) {
      state = PAUSE;
    } else {
    state = LIGHT_3;
  }
  // if (score > 0) {
  // score--;
// }
    break;
    case LIGHT_3:
    if (button) {
      state = PAUSE;
    } else {
    state = LIGHT_1;
  }
  // if (score > 0) {
  // score--;
// }
    break;
    case PAUSE:
    if (!button) {
    switch(FLAGERINO) {
      case 1:
      state = LIGHT_1;
      // score++;
      score += 2;
      break;
      case 2:
      state = LIGHT_2;
      // score++;
      score += 2;
      break;
      case 3:
      state = LIGHT_3;
      score += 2;
            break;
    }
    // score--;
    FLAGERINO = 0;
  } else {
    state = PAUSE;
    // score--;
  }
    break;
    default:
    score--;
    state = START;
    break;
  }
  switch(state) {
    case START:
    if (score > 0) {
    score--;
  }
    break;
    case LIGHT_1:
    output = 0x01;
    FLAGERINO = 1;
    // score++;
    break;
    case LIGHT_2:
    output = 0x02;
      FLAGERINO = 2;
      // score++;
    break;
    case LIGHT_3:
    output = 0x04;
      FLAGERINO = 3;
      // score++;
    break;
    case PAUSE:
    output = output;
    break;
    default:
    state = START;
    // score--;
    break;
  }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00;
    PORTA = 0xFF;
    DDRC = 0xFF;
    PORTC = 0x00;
    DDRD = 0xFF;
    PORTD = 0x00;
    DDRB = 0xFF;
    PORTB = 0x00;
    state = START;
    TimerSet(50);
    TimerOn();
    LCD_init();
    LCD_Cursor(1);
    score = 5;
    while (1) {
    LCD_ClearScreen();
      tick();
                  if (score >= 9) {
                    LCD_DisplayString(1, "YOU WON (VICTORY)!");
                    // return;
                    break;
                  } else {
            LCD_WriteData(score + '0');
          }
      while (!TimerFlag) {

      }
      TimerFlag = 0;
      PORTB = output;
      // PORTC = output;
    }
    return 1;
}