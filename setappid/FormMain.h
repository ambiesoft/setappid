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

	private: System::Windows::Forms::Button^  btnClose;



	private: System::Windows::Forms::ContextMenuStrip^  ctxList;
	private: System::Windows::Forms::ToolStripMenuItem^  copyAppIDToolStripMenuItem;

	private: System::Windows::Forms::ToolStripMenuItem^  setNewAppIDToolStripMenuItem;
	private: System::Windows::Forms::Button^  btnProcess;
	private: System::Windows::Forms::Label^  lblExp;

	private: System::ComponentModel::IContainer^  components;
	private: System::Windows::Forms::MenuStrip^  menuMain;
	private: System::Windows::Forms::ToolStripMenuItem^  fileToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  quitToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  loadUserPinnedItemToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  dummyToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  helpToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  aboutToolStripMenuItem;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>

		static System::Resources::ResourceManager^ theResource_ = 
			gcnew System::Resources::ResourceManager(FormMain::typeid->Namespace + ".StringResource", System::Reflection::Assembly::GetExecutingAssembly());
	internal:
		static String^ getI18NString(String^ sIn);

	private:
#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(FormMain::typeid));
			this->listMain = (gcnew System::Windows::Forms::ListView());
			this->clShortcut = (gcnew System::Windows::Forms::ColumnHeader());
			this->clAppID = (gcnew System::Windows::Forms::ColumnHeader());
			this->ctxList = (gcnew System::Windows::Forms::ContextMenuStrip(this->components));
			this->copyAppIDToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->setNewAppIDToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->btnClose = (gcnew System::Windows::Forms::Button());
			this->btnProcess = (gcnew System::Windows::Forms::Button());
			this->lblExp = (gcnew System::Windows::Forms::Label());
			this->menuMain = (gcnew System::Windows::Forms::MenuStrip());
			this->fileToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->quitToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->loadUserPinnedItemToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dummyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->helpToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->aboutToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ctxList->SuspendLayout();
			this->menuMain->SuspendLayout();
			this->SuspendLayout();
			// 
			// listMain
			// 
			resources->ApplyResources(this->listMain, L"listMain");
			this->listMain->AllowDrop = true;
			this->listMain->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) { this->clShortcut, this->clAppID });
			this->listMain->ContextMenuStrip = this->ctxList;
			this->listMain->Name = L"listMain";
			this->listMain->UseCompatibleStateImageBehavior = false;
			this->listMain->View = System::Windows::Forms::View::Details;
			this->listMain->DragDrop += gcnew System::Windows::Forms::DragEventHandler(this, &FormMain::listMain_DragDrop);
			this->listMain->DragOver += gcnew System::Windows::Forms::DragEventHandler(this, &FormMain::listMain_DragOver);
			// 
			// clShortcut
			// 
			resources->ApplyResources(this->clShortcut, L"clShortcut");
			// 
			// clAppID
			// 
			resources->ApplyResources(this->clAppID, L"clAppID");
			// 
			// ctxList
			// 
			resources->ApplyResources(this->ctxList, L"ctxList");
			this->ctxList->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->copyAppIDToolStripMenuItem,
					this->setNewAppIDToolStripMenuItem
			});
			this->ctxList->Name = L"ctxList";
			// 
			// copyAppIDToolStripMenuItem
			// 
			resources->ApplyResources(this->copyAppIDToolStripMenuItem, L"copyAppIDToolStripMenuItem");
			this->copyAppIDToolStripMenuItem->Name = L"copyAppIDToolStripMenuItem";
			this->copyAppIDToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::copyCuurentAppIDToolStripMenuItem_Click);
			// 
			// setNewAppIDToolStripMenuItem
			// 
			resources->ApplyResources(this->setNewAppIDToolStripMenuItem, L"setNewAppIDToolStripMenuItem");
			this->setNewAppIDToolStripMenuItem->Name = L"setNewAppIDToolStripMenuItem";
			this->setNewAppIDToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::setNewAppIDToolStripMenuItem_Click);
			// 
			// btnClose
			// 
			resources->ApplyResources(this->btnClose, L"btnClose");
			this->btnClose->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->btnClose->Name = L"btnClose";
			this->btnClose->UseVisualStyleBackColor = true;
			this->btnClose->Click += gcnew System::EventHandler(this, &FormMain::btnClose_Click);
			// 
			// btnProcess
			// 
			resources->ApplyResources(this->btnProcess, L"btnProcess");
			this->btnProcess->Name = L"btnProcess";
			this->btnProcess->UseVisualStyleBackColor = true;
			this->btnProcess->Click += gcnew System::EventHandler(this, &FormMain::btnProcess_Click);
			// 
			// lblExp
			// 
			resources->ApplyResources(this->lblExp, L"lblExp");
			this->lblExp->Name = L"lblExp";
			// 
			// menuMain
			// 
			resources->ApplyResources(this->menuMain, L"menuMain");
			this->menuMain->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->fileToolStripMenuItem,
					this->loadUserPinnedItemToolStripMenuItem, this->helpToolStripMenuItem
			});
			this->menuMain->Name = L"menuMain";
			// 
			// fileToolStripMenuItem
			// 
			resources->ApplyResources(this->fileToolStripMenuItem, L"fileToolStripMenuItem");
			this->fileToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->quitToolStripMenuItem });
			this->fileToolStripMenuItem->Name = L"fileToolStripMenuItem";
			// 
			// quitToolStripMenuItem
			// 
			resources->ApplyResources(this->quitToolStripMenuItem, L"quitToolStripMenuItem");
			this->quitToolStripMenuItem->Name = L"quitToolStripMenuItem";
			// 
			// loadUserPinnedItemToolStripMenuItem
			// 
			resources->ApplyResources(this->loadUserPinnedItemToolStripMenuItem, L"loadUserPinnedItemToolStripMenuItem");
			this->loadUserPinnedItemToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->dummyToolStripMenuItem });
			this->loadUserPinnedItemToolStripMenuItem->Name = L"loadUserPinnedItemToolStripMenuItem";
			this->loadUserPinnedItemToolStripMenuItem->DropDownOpening += gcnew System::EventHandler(this, &FormMain::loadUserPinnedItemToolStripMenuItem_DropDownOpening);
			// 
			// dummyToolStripMenuItem
			// 
			resources->ApplyResources(this->dummyToolStripMenuItem, L"dummyToolStripMenuItem");
			this->dummyToolStripMenuItem->Name = L"dummyToolStripMenuItem";
			// 
			// helpToolStripMenuItem
			// 
			resources->ApplyResources(this->helpToolStripMenuItem, L"helpToolStripMenuItem");
			this->helpToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->aboutToolStripMenuItem });
			this->helpToolStripMenuItem->Name = L"helpToolStripMenuItem";
			// 
			// aboutToolStripMenuItem
			// 
			resources->ApplyResources(this->aboutToolStripMenuItem, L"aboutToolStripMenuItem");
			this->aboutToolStripMenuItem->Name = L"aboutToolStripMenuItem";
			this->aboutToolStripMenuItem->Click += gcnew System::EventHandler(this, &FormMain::aboutToolStripMenuItem_Click);
			// 
			// FormMain
			// 
			resources->ApplyResources(this, L"$this");
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->btnClose;
			this->Controls->Add(this->lblExp);
			this->Controls->Add(this->btnProcess);
			this->Controls->Add(this->btnClose);
			this->Controls->Add(this->listMain);
			this->Controls->Add(this->menuMain);
			this->MainMenuStrip = this->menuMain;
			this->Name = L"FormMain";
			this->ctxList->ResumeLayout(false);
			this->menuMain->ResumeLayout(false);
			this->menuMain->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void btnClose_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		this->Close();
	}

	private: 
		System::Void listMain_DragOver(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);
		System::Void listMain_DragDrop(System::Object^  sender, System::Windows::Forms::DragEventArgs^  e);
		System::Void copyCuurentAppIDToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void setNewAppIDToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void btnProcess_Click(System::Object^  sender, System::EventArgs^  e);
		System::Void loadUserPinnedItemToolStripMenuItem_DropDownOpening(System::Object^  sender, System::EventArgs^  e);
		System::Void OnUPItemClick(System::Object^  sender, System::EventArgs^  e);

		





















private:
	//ref class FormProcess;
	Form^ formProcess_;




	void AddToList(String^ fullpath);



	System::Void aboutToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e);

};
}

