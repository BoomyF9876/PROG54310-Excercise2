#include <iostream>

#pragma once

namespace OpenGL {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for ToolWindow
	/// </summary>
	public ref class ToolWindow : public System::Windows::Forms::Form
	{
	public:
		static float RenderRedChannel;
		static float RenderGreenChannel;
		static float RenderBlueChannel;
	private: System::Windows::Forms::CheckBox^ checkBoxRedChannel;
	private: System::Windows::Forms::CheckBox^ checkBoxGreenChannel;
	private: System::Windows::Forms::CheckBox^ checkBoxBlueChannel;
	private: System::Windows::Forms::Label^ label1;

	private: System::Windows::Forms::TrackBar^ rgbSlider;
	public:
		ToolWindow(void)
		{
			InitializeComponent();
			RenderRedChannel = checkBoxRedChannel->Checked;
			RenderGreenChannel = checkBoxGreenChannel->Checked;
			RenderBlueChannel = checkBoxBlueChannel->Checked;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ToolWindow()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

	private: System::Void checkBoxRedChannel_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		RenderRedChannel = checkBoxRedChannel->Checked;
	}
	private: System::Void checkBoxGreenChannel_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		RenderGreenChannel = checkBoxGreenChannel->Checked;
	}
	private: System::Void checkBoxBlueChannel_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
	{
		RenderBlueChannel = checkBoxBlueChannel->Checked;
	}

	#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->checkBoxRedChannel = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxGreenChannel = (gcnew System::Windows::Forms::CheckBox());
			this->checkBoxBlueChannel = (gcnew System::Windows::Forms::CheckBox());
			this->rgbSlider = (gcnew System::Windows::Forms::TrackBar());
			this->label1 = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->rgbSlider))->BeginInit();
			this->SuspendLayout();
			// 
			// checkBoxRedChannel
			// 
			this->checkBoxRedChannel->AutoSize = true;
			this->checkBoxRedChannel->Checked = true;
			this->checkBoxRedChannel->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBoxRedChannel->Location = System::Drawing::Point(34, 32);
			this->checkBoxRedChannel->Margin = System::Windows::Forms::Padding(2);
			this->checkBoxRedChannel->Name = L"checkBoxRedChannel";
			this->checkBoxRedChannel->Size = System::Drawing::Size(42, 16);
			this->checkBoxRedChannel->TabIndex = 0;
			this->checkBoxRedChannel->Text = L"Red";
			this->checkBoxRedChannel->UseVisualStyleBackColor = true;
			this->checkBoxRedChannel->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBoxRedChannel_CheckedChanged);
			// 
			// checkBoxGreenChannel
			// 
			this->checkBoxGreenChannel->AutoSize = true;
			this->checkBoxGreenChannel->Checked = true;
			this->checkBoxGreenChannel->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBoxGreenChannel->Location = System::Drawing::Point(34, 67);
			this->checkBoxGreenChannel->Margin = System::Windows::Forms::Padding(2);
			this->checkBoxGreenChannel->Name = L"checkBoxGreenChannel";
			this->checkBoxGreenChannel->Size = System::Drawing::Size(54, 16);
			this->checkBoxGreenChannel->TabIndex = 1;
			this->checkBoxGreenChannel->Text = L"Green";
			this->checkBoxGreenChannel->UseVisualStyleBackColor = true;
			this->checkBoxGreenChannel->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBoxGreenChannel_CheckedChanged);
			// 
			// checkBoxBlueChannel
			// 
			this->checkBoxBlueChannel->AutoSize = true;
			this->checkBoxBlueChannel->Checked = true;
			this->checkBoxBlueChannel->CheckState = System::Windows::Forms::CheckState::Checked;
			this->checkBoxBlueChannel->Location = System::Drawing::Point(34, 108);
			this->checkBoxBlueChannel->Margin = System::Windows::Forms::Padding(2);
			this->checkBoxBlueChannel->Name = L"checkBoxBlueChannel";
			this->checkBoxBlueChannel->Size = System::Drawing::Size(48, 16);
			this->checkBoxBlueChannel->TabIndex = 2;
			this->checkBoxBlueChannel->Text = L"Blue";
			this->checkBoxBlueChannel->UseVisualStyleBackColor = true;
			this->checkBoxBlueChannel->CheckedChanged += gcnew System::EventHandler(this, &ToolWindow::checkBoxBlueChannel_CheckedChanged);
			// 
			// rgbSlider
			// 
			this->rgbSlider->Location = System::Drawing::Point(108, 141);
			this->rgbSlider->Maximum = 100;
			this->rgbSlider->Name = L"rgbSlider";
			this->rgbSlider->Size = System::Drawing::Size(114, 45);
			this->rgbSlider->TabIndex = 3;
			this->rgbSlider->TickStyle = System::Windows::Forms::TickStyle::None;
			this->rgbSlider->Value = this->rgbSlider->Maximum;
			this->rgbSlider->Scroll += gcnew System::EventHandler(this, &ToolWindow::rgbSlider_Scroll);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"SimSun", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(134)));
			this->label1->Location = System::Drawing::Point(31, 143);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(77, 14);
			this->label1->TabIndex = 5;
			this->label1->Text = L"Intensity:";
			// 
			// ToolWindow
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(275, 191);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->rgbSlider);
			this->Controls->Add(this->checkBoxBlueChannel);
			this->Controls->Add(this->checkBoxGreenChannel);
			this->Controls->Add(this->checkBoxRedChannel);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"ToolWindow";
			this->Text = L"ToolWindow";
			this->TopMost = true;
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->rgbSlider))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
	#pragma endregion
	private: System::Void rgbSlider_Scroll(System::Object^ sender, System::EventArgs^ e) {
		float scale = (float)rgbSlider->Value / (float)rgbSlider->Maximum;
		RenderRedChannel = checkBoxRedChannel->Checked * scale;
		RenderGreenChannel = checkBoxGreenChannel->Checked * scale;
		RenderBlueChannel = checkBoxBlueChannel->Checked * scale;

		std::cout << "RGB: (" << RenderRedChannel<< ", " << RenderGreenChannel << ", " << RenderBlueChannel << ")\n";
	}
};
}
