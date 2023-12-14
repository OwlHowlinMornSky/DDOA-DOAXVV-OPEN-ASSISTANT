namespace WinFormsGUI {
	partial class FormMain {
		/// <summary>
		///  Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		///  Clean up any resources being used.
		/// </summary>
		/// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
		protected override void Dispose(bool disposing) {
			if (disposing && (components != null)) {
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region Windows Form Designer generated code

		/// <summary>
		///  Required method for Designer support - do not modify
		///  the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent() {
			components = new System.ComponentModel.Container();
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormMain));
			splitContainer_Tab0_Main = new SplitContainer();
			button_Tab0_Main = new Button();
			groupBox_Tab0_Box1 = new GroupBox();
			radioButton_Tab0_Box1_1 = new RadioButton();
			radioButton_Tab0_Box1_0 = new RadioButton();
			groupBox_Tab0_Box0 = new GroupBox();
			radioButton_Tab0_Box0_1 = new RadioButton();
			radioButton_Tab0_Box0_0 = new RadioButton();
			listBox_Main = new ListBox();
			tabControl_Main = new TabControl();
			tabPage_Main_0 = new TabPage();
			tabPage_Main_1 = new TabPage();
			timer1 = new System.Windows.Forms.Timer(components);
			((System.ComponentModel.ISupportInitialize)splitContainer_Tab0_Main).BeginInit();
			splitContainer_Tab0_Main.Panel1.SuspendLayout();
			splitContainer_Tab0_Main.Panel2.SuspendLayout();
			splitContainer_Tab0_Main.SuspendLayout();
			groupBox_Tab0_Box1.SuspendLayout();
			groupBox_Tab0_Box0.SuspendLayout();
			tabControl_Main.SuspendLayout();
			tabPage_Main_0.SuspendLayout();
			SuspendLayout();
			// 
			// splitContainer_Tab0_Main
			// 
			resources.ApplyResources(splitContainer_Tab0_Main, "splitContainer_Tab0_Main");
			splitContainer_Tab0_Main.FixedPanel = FixedPanel.Panel1;
			splitContainer_Tab0_Main.Name = "splitContainer_Tab0_Main";
			// 
			// splitContainer_Tab0_Main.Panel1
			// 
			splitContainer_Tab0_Main.Panel1.Controls.Add(button_Tab0_Main);
			splitContainer_Tab0_Main.Panel1.Controls.Add(groupBox_Tab0_Box1);
			splitContainer_Tab0_Main.Panel1.Controls.Add(groupBox_Tab0_Box0);
			// 
			// splitContainer_Tab0_Main.Panel2
			// 
			splitContainer_Tab0_Main.Panel2.Controls.Add(listBox_Main);
			// 
			// button_Tab0_Main
			// 
			resources.ApplyResources(button_Tab0_Main, "button_Tab0_Main");
			button_Tab0_Main.Name = "button_Tab0_Main";
			button_Tab0_Main.UseVisualStyleBackColor = true;
			button_Tab0_Main.Click += button_Tab0_Main_Click;
			// 
			// groupBox_Tab0_Box1
			// 
			groupBox_Tab0_Box1.Controls.Add(radioButton_Tab0_Box1_1);
			groupBox_Tab0_Box1.Controls.Add(radioButton_Tab0_Box1_0);
			resources.ApplyResources(groupBox_Tab0_Box1, "groupBox_Tab0_Box1");
			groupBox_Tab0_Box1.Name = "groupBox_Tab0_Box1";
			groupBox_Tab0_Box1.TabStop = false;
			// 
			// radioButton_Tab0_Box1_1
			// 
			resources.ApplyResources(radioButton_Tab0_Box1_1, "radioButton_Tab0_Box1_1");
			radioButton_Tab0_Box1_1.Name = "radioButton_Tab0_Box1_1";
			radioButton_Tab0_Box1_1.UseVisualStyleBackColor = true;
			radioButton_Tab0_Box1_1.CheckedChanged += radioButton_Tab0_Box1_1_CheckedChanged;
			// 
			// radioButton_Tab0_Box1_0
			// 
			resources.ApplyResources(radioButton_Tab0_Box1_0, "radioButton_Tab0_Box1_0");
			radioButton_Tab0_Box1_0.Checked = true;
			radioButton_Tab0_Box1_0.Name = "radioButton_Tab0_Box1_0";
			radioButton_Tab0_Box1_0.TabStop = true;
			radioButton_Tab0_Box1_0.UseVisualStyleBackColor = true;
			radioButton_Tab0_Box1_0.CheckedChanged += radioButton_Tab0_Box1_0_CheckedChanged;
			// 
			// groupBox_Tab0_Box0
			// 
			groupBox_Tab0_Box0.Controls.Add(radioButton_Tab0_Box0_1);
			groupBox_Tab0_Box0.Controls.Add(radioButton_Tab0_Box0_0);
			resources.ApplyResources(groupBox_Tab0_Box0, "groupBox_Tab0_Box0");
			groupBox_Tab0_Box0.Name = "groupBox_Tab0_Box0";
			groupBox_Tab0_Box0.TabStop = false;
			// 
			// radioButton_Tab0_Box0_1
			// 
			resources.ApplyResources(radioButton_Tab0_Box0_1, "radioButton_Tab0_Box0_1");
			radioButton_Tab0_Box0_1.Name = "radioButton_Tab0_Box0_1";
			radioButton_Tab0_Box0_1.UseVisualStyleBackColor = true;
			radioButton_Tab0_Box0_1.CheckedChanged += radioButton_Tab0_Box0_1_CheckedChanged;
			// 
			// radioButton_Tab0_Box0_0
			// 
			resources.ApplyResources(radioButton_Tab0_Box0_0, "radioButton_Tab0_Box0_0");
			radioButton_Tab0_Box0_0.Checked = true;
			radioButton_Tab0_Box0_0.Name = "radioButton_Tab0_Box0_0";
			radioButton_Tab0_Box0_0.TabStop = true;
			radioButton_Tab0_Box0_0.UseVisualStyleBackColor = true;
			radioButton_Tab0_Box0_0.CheckedChanged += radioButton_Tab0_Box0_0_CheckedChanged;
			// 
			// listBox_Main
			// 
			resources.ApplyResources(listBox_Main, "listBox_Main");
			listBox_Main.FormattingEnabled = true;
			listBox_Main.Name = "listBox_Main";
			listBox_Main.SelectionMode = SelectionMode.None;
			listBox_Main.TabStop = false;
			listBox_Main.UseTabStops = false;
			// 
			// tabControl_Main
			// 
			tabControl_Main.Controls.Add(tabPage_Main_0);
			tabControl_Main.Controls.Add(tabPage_Main_1);
			resources.ApplyResources(tabControl_Main, "tabControl_Main");
			tabControl_Main.Name = "tabControl_Main";
			tabControl_Main.SelectedIndex = 0;
			// 
			// tabPage_Main_0
			// 
			tabPage_Main_0.Controls.Add(splitContainer_Tab0_Main);
			resources.ApplyResources(tabPage_Main_0, "tabPage_Main_0");
			tabPage_Main_0.Name = "tabPage_Main_0";
			tabPage_Main_0.UseVisualStyleBackColor = true;
			// 
			// tabPage_Main_1
			// 
			resources.ApplyResources(tabPage_Main_1, "tabPage_Main_1");
			tabPage_Main_1.Name = "tabPage_Main_1";
			tabPage_Main_1.UseVisualStyleBackColor = true;
			// 
			// timer1
			// 
			timer1.Interval = 30;
			timer1.Tick += timer1_Tick;
			// 
			// FormMain
			// 
			resources.ApplyResources(this, "$this");
			AutoScaleMode = AutoScaleMode.Font;
			Controls.Add(tabControl_Main);
			Name = "FormMain";
			FormClosing += FormMain_FormClosing;
			FormClosed += FormMain_FormClosed;
			Load += FormMain_Load;
			splitContainer_Tab0_Main.Panel1.ResumeLayout(false);
			splitContainer_Tab0_Main.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)splitContainer_Tab0_Main).EndInit();
			splitContainer_Tab0_Main.ResumeLayout(false);
			groupBox_Tab0_Box1.ResumeLayout(false);
			groupBox_Tab0_Box1.PerformLayout();
			groupBox_Tab0_Box0.ResumeLayout(false);
			groupBox_Tab0_Box0.PerformLayout();
			tabControl_Main.ResumeLayout(false);
			tabPage_Main_0.ResumeLayout(false);
			ResumeLayout(false);
		}

		#endregion

		private TabControl tabControl_Main;
		private TabPage tabPage_Main_0;
		private TabPage tabPage_Main_1;
		private SplitContainer splitContainer_Tab0_Main;
		private Button button_Tab0_Main;
		private GroupBox groupBox_Tab0_Box1;
		private GroupBox groupBox_Tab0_Box0;
		private ListBox listBox_Main;
		private RadioButton radioButton_Tab0_Box1_1;
		private RadioButton radioButton_Tab0_Box1_0;
		private RadioButton radioButton_Tab0_Box0_1;
		private RadioButton radioButton_Tab0_Box0_0;
		private System.Windows.Forms.Timer timer1;
	}
}
