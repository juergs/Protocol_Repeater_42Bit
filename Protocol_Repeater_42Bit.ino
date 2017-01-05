#include <SerialCommand.h>

SerialCommand sCmd;     // The demo SerialCommand object

//------------------------------------------------------------------

//------------------------------------------------------------------
void setup() 
{
	pinMode(LED_BUILTIN , OUTPUT);      // Configure the onboard LED for output
	digitalWrite(LED_BUILTIN, LOW);    // default to LED off

	Serial.begin(57600);

	// Setup callbacks for SerialCommand commands
	sCmd.addCommand("ON", LED_on);          // Turns LED on
	sCmd.addCommand("OFF", LED_off);         // Turns LED off
	sCmd.addCommand("BLINK", Blink);         // Turns LED off
	sCmd.addCommand("HELLO", sayHello);        // Echos the string argument back
	sCmd.addCommand("P", processCommand);  // Converts two arguments to integers and echos them back
	sCmd.setDefaultHandler(unrecognized);      // Handler for command that isn't matched  (says "What?")
	Serial.println("*** Ready for processing serial commands... ");
}
//------------------------------------------------------------------
void loop()
{

  sCmd.readSerial();     // We don't do much, just process serial commands
}
// ------------------------------------------------------------------
void LED_on()
{
	Serial.println("LED on");
	digitalWrite(LED_BUILTIN, HIGH);
}
//------------------------------------------------------------------
void LED_off()
{
	Serial.println("LED off");
	digitalWrite(LED_BUILTIN, LOW);
}
//------------------------------------------------------------------
void Blink()
{
	Serial.println("Blinking...");
	for (byte i=0; i<10; i++)
	{
		digitalWrite(LED_BUILTIN, HIGH);
		delay(100);
		digitalWrite(LED_BUILTIN, LOW);
		delay(200);
	}
	Serial.println("Blink done.");
}

//------------------------------------------------------------------
void sayHello()
{
	char *arg;
	arg = sCmd.next();    // Get the next argument from the SerialCommand object buffer
	if (arg != NULL)
	{
		// As long as it existed, take it
		Serial.print("Hello ");
		Serial.println(arg);
	}
	else
	{
		Serial.println("Hello, whoever you are");
	}
}
//------------------------------------------------------------------
void processCommand()
{
	int aNumber;
	char *arg;

	Serial.println("We're in processCommand");
	arg = sCmd.next();
	if (arg != NULL)
	{
		aNumber = atoi(arg);    // Converts a char string to an integer
		Serial.print("First argument was: ");
		Serial.println(aNumber);
	}
	else
	{
		Serial.println("No arguments");
	}

	arg = sCmd.next();
	if (arg != NULL)
	{
		aNumber = atol(arg);
		Serial.print("Second argument was: ");
		Serial.println(aNumber);
	}
	else
	{
		Serial.println("No second argument");
	}
}
//------------------------------------------------------------------
// This gets set as the default handler, and gets called when no other command matches.
void unrecognized(const char *command)
{
	Serial.println("What?");
}
//------------------------------------------------------------------
//------------------------------------------------------------------