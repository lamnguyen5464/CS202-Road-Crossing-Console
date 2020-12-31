#include "header.h"

int main() {
	sportApp app;
	proScoreDisplay pro;
	normalScoreDisplay normal;
	
	app.registerObsever(&normal);
	app.registerObsever(&pro);
	app.editScore("James",3,2);
	pro.display();
	normal.display();

	app.unregisterObserver(&pro);
	app.editScore("Kelvin", 3, 3);
	normal.display();
	pro.display();
	return 0;
}