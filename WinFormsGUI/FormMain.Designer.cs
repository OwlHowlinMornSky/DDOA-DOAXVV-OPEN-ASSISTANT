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
			btn_home_main = new Button();
			gpBox_home_ctrlSet = new GroupBox();
			radioBtn_home_ctrlInput = new RadioButton();
			radioBtn_home_ctrlMsg = new RadioButton();
			gpBox_home_gameSet = new GroupBox();
			radioBtn_home_gameNew = new RadioButton();
			radioBtn_home_gameLast = new RadioButton();
			listBox_home = new ListBox();
			tabControl_main = new TabControl();
			tabPage_main_home = new TabPage();
			tabPage_main_settings = new TabPage();
			checkBox_settings_useNotify = new CheckBox();
			checkBox_settings_hideToIcon = new CheckBox();
			checkBox_settings_showCV = new CheckBox();
			timer_main = new System.Windows.Forms.Timer(components);
			notifyIcon_main = new NotifyIcon(components);
			ctxtMenu_notifyR = new ContextMenuStrip(components);
			ctxtMenu_notifyR_exit = new ToolStripMenuItem();
			((System.ComponentModel.ISupportInitialize)splitContainer_Tab0_Main).BeginInit();
			splitContainer_Tab0_Main.Panel1.SuspendLayout();
			splitContainer_Tab0_Main.Panel2.SuspendLayout();
			splitContainer_Tab0_Main.SuspendLayout();
			gpBox_home_ctrlSet.SuspendLayout();
			gpBox_home_gameSet.SuspendLayout();
			tabControl_main.SuspendLayout();
			tabPage_main_home.SuspendLayout();
			tabPage_main_settings.SuspendLayout();
			ctxtMenu_notifyR.SuspendLayout();
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
			splitContainer_Tab0_Main.Panel1.Controls.Add(btn_home_main);
			splitContainer_Tab0_Main.Panel1.Controls.Add(gpBox_home_ctrlSet);
			splitContainer_Tab0_Main.Panel1.Controls.Add(gpBox_home_gameSet);
			// 
			// splitContainer_Tab0_Main.Panel2
			// 
			splitContainer_Tab0_Main.Panel2.Controls.Add(listBox_home);
			// 
			// btn_home_main
			// 
			resources.ApplyResources(btn_home_main, "btn_home_main");
			btn_home_main.Name = "btn_home_main";
			btn_home_main.UseVisualStyleBackColor = true;
			btn_home_main.Click += btn_home_main_Click;
			// 
			// gpBox_home_ctrlSet
			// 
			gpBox_home_ctrlSet.Controls.Add(radioBtn_home_ctrlInput);
			gpBox_home_ctrlSet.Controls.Add(radioBtn_home_ctrlMsg);
			resources.ApplyResources(gpBox_home_ctrlSet, "gpBox_home_ctrlSet");
			gpBox_home_ctrlSet.Name = "gpBox_home_ctrlSet";
			gpBox_home_ctrlSet.TabStop = false;
			// 
			// radioBtn_home_ctrlInput
			// 
			resources.ApplyResources(radioBtn_home_ctrlInput, "radioBtn_home_ctrlInput");
			radioBtn_home_ctrlInput.Name = "radioBtn_home_ctrlInput";
			radioBtn_home_ctrlInput.UseVisualStyleBackColor = true;
			radioBtn_home_ctrlInput.CheckedChanged += radioBtn_home_ctrl_CheckedChanged;
			// 
			// radioBtn_home_ctrlMsg
			// 
			resources.ApplyResources(radioBtn_home_ctrlMsg, "radioBtn_home_ctrlMsg");
			radioBtn_home_ctrlMsg.Checked = true;
			radioBtn_home_ctrlMsg.Name = "radioBtn_home_ctrlMsg";
			radioBtn_home_ctrlMsg.TabStop = true;
			radioBtn_home_ctrlMsg.UseVisualStyleBackColor = true;
			radioBtn_home_ctrlMsg.CheckedChanged += radioBtn_home_ctrl_CheckedChanged;
			// 
			// gpBox_home_gameSet
			// 
			gpBox_home_gameSet.Controls.Add(radioBtn_home_gameNew);
			gpBox_home_gameSet.Controls.Add(radioBtn_home_gameLast);
			resources.ApplyResources(gpBox_home_gameSet, "gpBox_home_gameSet");
			gpBox_home_gameSet.Name = "gpBox_home_gameSet";
			gpBox_home_gameSet.TabStop = false;
			// 
			// radioBtn_home_gameNew
			// 
			resources.ApplyResources(radioBtn_home_gameNew, "radioBtn_home_gameNew");
			radioBtn_home_gameNew.Name = "radioBtn_home_gameNew";
			radioBtn_home_gameNew.UseVisualStyleBackColor = true;
			radioBtn_home_gameNew.CheckedChanged += radioBtn_home_game_CheckedChanged;
			// 
			// radioBtn_home_gameLast
			// 
			resources.ApplyResources(radioBtn_home_gameLast, "radioBtn_home_gameLast");
			radioBtn_home_gameLast.Checked = true;
			radioBtn_home_gameLast.Name = "radioBtn_home_gameLast";
			radioBtn_home_gameLast.TabStop = true;
			radioBtn_home_gameLast.UseVisualStyleBackColor = true;
			radioBtn_home_gameLast.CheckedChanged += radioBtn_home_game_CheckedChanged;
			// 
			// listBox_home
			// 
			resources.ApplyResources(listBox_home, "listBox_home");
			listBox_home.FormattingEnabled = true;
			listBox_home.Name = "listBox_home";
			listBox_home.SelectionMode = SelectionMode.None;
			listBox_home.TabStop = false;
			listBox_home.UseTabStops = false;
			// 
			// tabControl_main
			// 
			tabControl_main.Controls.Add(tabPage_main_home);
			tabControl_main.Controls.Add(tabPage_main_settings);
			resources.ApplyResources(tabControl_main, "tabControl_main");
			tabControl_main.Name = "tabControl_main";
			tabControl_main.SelectedIndex = 0;
			// 
			// tabPage_main_home
			// 
			tabPage_main_home.Controls.Add(splitContainer_Tab0_Main);
			resources.ApplyResources(tabPage_main_home, "tabPage_main_home");
			tabPage_main_home.Name = "tabPage_main_home";
			tabPage_main_home.UseVisualStyleBackColor = true;
			// 
			// tabPage_main_settings
			// 
			tabPage_main_settings.Controls.Add(checkBox_settings_useNotify);
			tabPage_main_settings.Controls.Add(checkBox_settings_hideToIcon);
			tabPage_main_settings.Controls.Add(checkBox_settings_showCV);
			resources.ApplyResources(tabPage_main_settings, "tabPage_main_settings");
			tabPage_main_settings.Name = "tabPage_main_settings";
			tabPage_main_settings.UseVisualStyleBackColor = true;
			// 
			// checkBox_settings_useNotify
			// 
			resources.ApplyResources(checkBox_settings_useNotify, "checkBox_settings_useNotify");
			checkBox_settings_useNotify.Name = "checkBox_settings_useNotify";
			checkBox_settings_useNotify.UseVisualStyleBackColor = true;
			checkBox_settings_useNotify.CheckedChanged += checkBox_settings_useNotify_CheckedChanged;
			// 
			// checkBox_settings_hideToIcon
			// 
			resources.ApplyResources(checkBox_settings_hideToIcon, "checkBox_settings_hideToIcon");
			checkBox_settings_hideToIcon.Name = "checkBox_settings_hideToIcon";
			checkBox_settings_hideToIcon.UseVisualStyleBackColor = true;
			checkBox_settings_hideToIcon.CheckedChanged += checkBox_settings_hideToIcon_CheckedChanged;
			// 
			// checkBox_settings_showCV
			// 
			resources.ApplyResources(checkBox_settings_showCV, "checkBox_settings_showCV");
			checkBox_settings_showCV.Name = "checkBox_settings_showCV";
			checkBox_settings_showCV.UseVisualStyleBackColor = true;
			checkBox_settings_showCV.CheckedChanged += checkBox_settings_showCV_CheckedChanged;
			// 
			// timer_main
			// 
			timer_main.Interval = 50;
			timer_main.Tick += timer_main_Tick;
			// 
			// notifyIcon_main
			// 
			notifyIcon_main.ContextMenuStrip = ctxtMenu_notifyR;
			resources.ApplyResources(notifyIcon_main, "notifyIcon_main");
			notifyIcon_main.MouseClick += notifyIcon_main_MouseClick;
			// 
			// ctxtMenu_notifyR
			// 
			ctxtMenu_notifyR.Items.AddRange(new ToolStripItem[] { ctxtMenu_notifyR_exit });
			ctxtMenu_notifyR.Name = "ctxtMenu_notifyR";
			ctxtMenu_notifyR.RenderMode = ToolStripRenderMode.System;
			resources.ApplyResources(ctxtMenu_notifyR, "ctxtMenu_notifyR");
			// 
			// ctxtMenu_notifyR_exit
			// 
			ctxtMenu_notifyR_exit.Name = "ctxtMenu_notifyR_exit";
			resources.ApplyResources(ctxtMenu_notifyR_exit, "ctxtMenu_notifyR_exit");
			ctxtMenu_notifyR_exit.Click += ctxtMenu_notifyR_exit_Click;
			// 
			// FormMain
			// 
			resources.ApplyResources(this, "$this");
			AutoScaleMode = AutoScaleMode.Font;
			Controls.Add(tabControl_main);
			Name = "FormMain";
			Deactivate += FormMain_Deactivate;
			FormClosing += FormMain_FormClosing;
			FormClosed += FormMain_FormClosed;
			Load += FormMain_Load;
			splitContainer_Tab0_Main.Panel1.ResumeLayout(false);
			splitContainer_Tab0_Main.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)splitContainer_Tab0_Main).EndInit();
			splitContainer_Tab0_Main.ResumeLayout(false);
			gpBox_home_ctrlSet.ResumeLayout(false);
			gpBox_home_ctrlSet.PerformLayout();
			gpBox_home_gameSet.ResumeLayout(false);
			gpBox_home_gameSet.PerformLayout();
			tabControl_main.ResumeLayout(false);
			tabPage_main_home.ResumeLayout(false);
			tabPage_main_settings.ResumeLayout(false);
			tabPage_main_settings.PerformLayout();
			ctxtMenu_notifyR.ResumeLayout(false);
			ResumeLayout(false);
		}

		#endregion

		private TabControl tabControl_main;
		private TabPage tabPage_main_home;
		private TabPage tabPage_main_settings;
		private SplitContainer splitContainer_Tab0_Main;
		private Button btn_home_main;
		private GroupBox gpBox_home_ctrlSet;
		private GroupBox gpBox_home_gameSet;
		private ListBox listBox_home;
		private RadioButton radioBtn_home_ctrlInput;
		private RadioButton radioBtn_home_ctrlMsg;
		private RadioButton radioBtn_home_gameNew;
		private RadioButton radioBtn_home_gameLast;
		private System.Windows.Forms.Timer timer_main;
		private CheckBox checkBox_settings_showCV;
		private NotifyIcon notifyIcon_main;
		private ContextMenuStrip ctxtMenu_notifyR;
		private CheckBox checkBox_settings_hideToIcon;
		private CheckBox checkBox_settings_useNotify;
		private ToolStripMenuItem ctxtMenu_notifyR_exit;
	}
}
