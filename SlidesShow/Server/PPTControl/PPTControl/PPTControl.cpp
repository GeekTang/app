// PPTControl.cpp : main project file.

#include "stdafx.h"
#include "string"

#using <System.Drawing.dll>
#using <System.Windows.Forms.dll>
#using <System.dll>

using namespace System;
using namespace System::Runtime::InteropServices;
using namespace System::Drawing;
using namespace System::Windows::Forms;

namespace SimulateKeyPress
{

    public ref class Form1 : public Form
    {
    public:
        Form1()
        {
            Button^ button1 = gcnew Button();
            button1->Location = Point(10, 10);
            button1->TabIndex = 0;
            button1->Text = "Click to automate Calculator";
            button1->AutoSize = true;
            button1->Click += gcnew EventHandler(this, &Form1::button1_Click);

            this->DoubleClick += gcnew EventHandler(this, 
                &Form1::Form1_DoubleClick);
            this->Controls->Add(button1);
        }

        // Get a handle to an application window.
	public:
		[DllImport("USER32.DLL")]
		static IntPtr FindWindow(String^ lpClassName, String^ lpWindowName);
	public:
		// Activate an application window.
		[DllImport("USER32.DLL")]
		static bool SetForegroundWindow(IntPtr hWnd);
	public:
		[DllImport("user32.dll", SetLastError = true)]
		static IntPtr FindWindowEx(IntPtr parentHandle, IntPtr childAfter, String^  className,  String^  windowTitle);

		// Send a series of key presses to the Calculator application.
	private:
		void button1_Click(Object^ sender, EventArgs^ e)
		{
			// Get a handle to the Calculator application. The window class
			// and window name were obtained using the Spy++ tool.
			IntPtr powerpoint = FindWindow("screenClass", nullptr);
			SetForegroundWindow(powerpoint);

			SendKeys::Send("{PGDN}");
			IntPtr slideShow = FindWindowEx(powerpoint,IntPtr::Zero,"paneClassDC",nullptr);

			// Verify that Calculator is a running process.
			if (powerpoint == IntPtr::Zero)
			{
				MessageBox::Show("Powerpoint is not running.");
				return;
			}

			if (slideShow == IntPtr::Zero)
            {
                MessageBox::Show("Slides are not show.");
                return;
            }

            // Make Calculator the foreground application and send it
            // a set of calculations.
            SetForegroundWindow(slideShow);

			SendKeys::Send("{PGDN}");
			
            //SendKeys::SendWait("111");
            //SendKeys::SendWait("*");
            //SendKeys::SendWait("11");
            //SendKeys::SendWait("=");
        }

        // Send a key to the button when the user double-clicks anywhere
        // on the form.
    private:
        void Form1_DoubleClick(Object^ sender, EventArgs^ e)
        {
            // Send the enter key to the button, which triggers the click
			// event for the button. This works because the tab stop of
            // the button is 0.
            SendKeys::Send("{ENTER}");
        }
    };
}

[STAThread]
int main()
{
    Application::EnableVisualStyles();
    Application::Run(gcnew SimulateKeyPress::Form1());
}
