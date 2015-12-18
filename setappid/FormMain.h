#pragma once


namespace setappid {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for FormMain
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class FormMain : public System::Windows::Forms::Form
	{
	public:
		FormMain(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~FormMain()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListView^  listMain;
	protected: 

	protected: 
	private: System::Windows::Forms::ColumnHeader^  clShortcut;
	private: System::Windows::Forms::ColumnHeader^  clAppID;
	private: System::Windows::Forms::Button^  button1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->listMain = (gcnew System::Windows::Forms::ListView());
			this->clShortcut = (gcnew System::Windows::Forms::ColumnHeader());
			this->clAppID = (gcnew System::Windows::Forms::ColumnHeader());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// listMain
			// 
			this->listMain->AllowDrop = true;
			this->listMain->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) {this->clShortcut, this->clAppID});
			this->listMain->Location = System::Drawing::Point(12, 46);
			this->listMain->Name = L"listMain";
			this->listMain->Size = System::Drawing::Size(512, 165);
			this->listMain->TabIndex = 0;
			this->listMain->UseCompatibleStateImageBehavior = false;
			this->listMain->View = System::Windows::Forms::View::Details;
			this->listMain->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &FormMain::listMain_DragDrop);
			this->listMain->DragOver += gcnew System::Windows::Forms::DragEventHandler(this, &FormMain::listMain_DragOver);
			// 
			// clShortcut
			// 
			this->clShortcut->Text = L"Shortcut";
			this->clShortcut->Width = 369;
			// 
			// clAppID
			// 
			this->clAppID->Text = L"AppID";
			this->clAppID->Width = 99;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(412, 228);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(112, 31);
			this->button1->TabIndex = 1;
			this->button1->Text = L"button1";
			this->button1->UseVisualStyleBackColor = true;
			// 
			// FormMain
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(536, 271);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->listMain);
			this->Name = L"FormMain";
			this->Text = L"Set AppID";
			this->ResumeLayout(false);

		}
#pragma endregion

	private: System::Void listMain_DragOver(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e) {
				 if(e->Data->GetDataPresent(DataFormats::FileDrop))
					 e->Effect = DragDropEffects::Copy;
		
				 return;
			 }
	private: System::Void listMain_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);





	};
}

