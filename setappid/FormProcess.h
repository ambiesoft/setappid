#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace setappid {

	/// <summary>
	/// FormProcess の概要
	///
	/// 警告: このクラスの名前を変更する場合、このクラスが依存するすべての .resx ファイルに関連付けられた
	///          マネージ リソース コンパイラ ツールに対して 'Resource File Name' プロパティを
	///          変更する必要があります。この変更を行わないと、
	///          デザイナと、このフォームに関連付けられたローカライズ済みリソースとが、
	///          正しく相互に利用できなくなります。
	/// </summary>
	public ref class FormProcess : public System::Windows::Forms::Form
	{
	public:
		FormProcess(void)
		{
			InitializeComponent();
			//
			//TODO: ここにコンストラクタ コードを追加します
			//
		}

	protected:
		/// <summary>
		/// 使用中のリソースをすべてクリーンアップします。
		/// </summary>
		~FormProcess()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListView^  listMain;
	private: System::Windows::Forms::ColumnHeader^  clProcess;
	protected:

	private: System::Windows::Forms::ColumnHeader^  clAppID;
	private: System::Windows::Forms::Button^  btnClose;

	private:
		/// <summary>
		/// 必要なデザイナ変数です。
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// デザイナ サポートに必要なメソッドです。このメソッドの内容を
		/// コード エディタで変更しないでください。
		/// </summary>
		void InitializeComponent(void)
		{
			this->listMain = (gcnew System::Windows::Forms::ListView());
			this->clProcess = (gcnew System::Windows::Forms::ColumnHeader());
			this->clAppID = (gcnew System::Windows::Forms::ColumnHeader());
			this->btnClose = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// listMain
			// 
			this->listMain->AllowDrop = true;
			this->listMain->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Left)
				| System::Windows::Forms::AnchorStyles::Right));
			this->listMain->Columns->AddRange(gcnew cli::array< System::Windows::Forms::ColumnHeader^  >(2) { this->clProcess, this->clAppID });
			this->listMain->Location = System::Drawing::Point(12, 12);
			this->listMain->Name = L"listMain";
			this->listMain->Size = System::Drawing::Size(639, 206);
			this->listMain->TabIndex = 1;
			this->listMain->UseCompatibleStateImageBehavior = false;
			this->listMain->View = System::Windows::Forms::View::Details;
			// 
			// clProcess
			// 
			this->clProcess->Text = L"Process";
			this->clProcess->Width = 312;
			// 
			// clAppID
			// 
			this->clAppID->Text = L"AppID";
			this->clAppID->Width = 164;
			// 
			// btnClose
			// 
			this->btnClose->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btnClose->DialogResult = System::Windows::Forms::DialogResult::Cancel;
			this->btnClose->Location = System::Drawing::Point(539, 228);
			this->btnClose->Name = L"btnClose";
			this->btnClose->Size = System::Drawing::Size(112, 31);
			this->btnClose->TabIndex = 3;
			this->btnClose->Text = L"&Close";
			this->btnClose->UseVisualStyleBackColor = true;
			this->btnClose->Click += gcnew System::EventHandler(this, &FormProcess::btnClose_Click);
			// 
			// FormProcess
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->CancelButton = this->btnClose;
			this->ClientSize = System::Drawing::Size(663, 271);
			this->Controls->Add(this->btnClose);
			this->Controls->Add(this->listMain);
			this->Name = L"FormProcess";
			this->Text = L"FormProcess";
			this->Load += gcnew System::EventHandler(this, &FormProcess::FormProcess_Load);
			this->ResumeLayout(false);

		}
#pragma endregion

	private:
		System::Void FormProcess_Load(System::Object^  sender, System::EventArgs^  e);
		System::Void btnClose_Click(System::Object^  sender, System::EventArgs^  e)
		{
			this->Close();
		}

















};
}
