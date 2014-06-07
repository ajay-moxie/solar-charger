CC='C:\Program Files\HI-TECH Software\PICC\9.83\bin\picc.exe'
OBJECTS= ADC.p1 Charging.p1 Intensity_Switch.p1 LED.p1 Load_Switch.p1 PWM.p1 SYSTEM.p1 TIMER.p1 temp.p1 interrupt.p1 main.p1 led_load.p1 battery_mgmt.p1 load_mgmt.p1
DEPS= ADC.h Charging.h intensity_switch.h LED.h Load_Switch.h PWM.h SYSTEM.h TIMER.h temp.h interrupt.h led_load.h pi.h battery_mgmt.h common.h load_mgmt.h
CFLAGS= -q --chip=16F1509 -P --runtime=default,+clear,+init,-keep,+osccal,-download,-resetbits,-stackcall,+clib --opt=default,+asm,-debug,-speed,+space,9 --warn=0 -D__DEBUG=1 --double=24 --float=24 --addrqual=ignore -g --asmlist

all:	solar-charger.hex
solar-charger.hex:	$(OBJECTS)
	$(CC) -osolar-charger.cof -msolar-charger.map --summary=default,-psect,-class,+mem,-hex --output=default,-inhx032 $(OBJECTS) $(CFLAGS)

%.p1:	%.c $(DEPS)
	$(CC) --pass1 $< $(CFLAGS)

sl:
	cp configs/sl.config config.h

clean:
	rm -f $(OBJECTS) *.hex *.p1 *.pre *.obj *.rlf *.sdb *.hxl *.map *.sym *.cof *.sdb *.dep *.mcs *.lst *.as *.plt config.h
