// setappid.cpp : main project file.

#include "stdafx.h"

#include "FormMain.h"

using namespace System;
using namespace setappid;

[STAThreadAttribute]
int main(array<System::String ^> ^args)
{
	// Enabling Windows XP visual effects before any controls are created
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false); 

	// Create the main window and run it
	Application::Run(gcnew FormMain());
	return 0;
}


