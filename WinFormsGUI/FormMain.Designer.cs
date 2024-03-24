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
			timer_main = new System.Windows.Forms.Timer(components);
			notifyIcon_main = new NotifyIcon(components);
			ctxtMenu_notifyR = new ContextMenuStrip(components);
			ctxtMenu_notifyR_exit = new ToolStripMenuItem();
			tabPage_Set = new TabPage();
			label_TransValue = new Label();
			label_TransTitle = new Label();
			chkBox_SetDisableClose = new CheckBox();
			tkBar_Trans = new TrackBar();
			chkBox_SetScreenOn = new CheckBox();
			chkBox_SetAwake = new CheckBox();
			chkBox_SetNotify = new CheckBox();
			chkBox_SetHideToTray = new CheckBox();
			chkBox_SetShow = new CheckBox();
			tabPage_Home = new TabPage();
			splitContainer0 = new SplitContainer();
			gpBox_AwardSet = new GroupBox();
			radioBtn_AwardIgnore = new RadioButton();
			radioBtn_AwardPlay = new RadioButton();
			radioBtn_AwardNo = new RadioButton();
			btn_Main = new Button();
			gpBox_CtrlSet = new GroupBox();
			radioBtn_CtrlInput = new RadioButton();
			radioBtn_CtrlMsg = new RadioButton();
			gpBox_GameSet = new GroupBox();
			radioBtn_GameNew = new RadioButton();
			radioBtn_GameLast = new RadioButton();
			listBox_Log = new ListBox();
			tabControl0 = new TabControl();
			ctxtMenu_notifyR.SuspendLayout();
			tabPage_Set.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)tkBar_Trans).BeginInit();
			tabPage_Home.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)splitContainer0).BeginInit();
			splitContainer0.Panel1.SuspendLayout();
			splitContainer0.Panel2.SuspendLayout();
			splitContainer0.SuspendLayout();
			gpBox_AwardSet.SuspendLayout();
			gpBox_CtrlSet.SuspendLayout();
			gpBox_GameSet.SuspendLayout();
			tabControl0.SuspendLayout();
			SuspendLayout();
			// 
			// timer_main
			// 
			timer_main.Interval = 30;
			timer_main.Tick += Timer_main_Tick;
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
			// tabPage_Set
			// 
			tabPage_Set.Controls.Add(label_TransValue);
			tabPage_Set.Controls.Add(label_TransTitle);
			tabPage_Set.Controls.Add(chkBox_SetDisableClose);
			tabPage_Set.Controls.Add(tkBar_Trans);
			tabPage_Set.Controls.Add(chkBox_SetScreenOn);
			tabPage_Set.Controls.Add(chkBox_SetAwake);
			tabPage_Set.Controls.Add(chkBox_SetNotify);
			tabPage_Set.Controls.Add(chkBox_SetHideToTray);
			tabPage_Set.Controls.Add(chkBox_SetShow);
			resources.ApplyResources(tabPage_Set, "tabPage_Set");
			tabPage_Set.Name = "tabPage_Set";
			tabPage_Set.UseVisualStyleBackColor = true;
			// 
			// label_TransValue
			// 
			resources.ApplyResources(label_TransValue, "label_TransValue");
			label_TransValue.Name = "label_TransValue";
			label_TransValue.SizeChanged += label_transp_value_SizeChanged;
			// 
			// label_TransTitle
			// 
			resources.ApplyResources(label_TransTitle, "label_TransTitle");
			label_TransTitle.Name = "label_TransTitle";
			// 
			// chkBox_SetDisableClose
			// 
			resources.ApplyResources(chkBox_SetDisableClose, "chkBox_SetDisableClose");
			chkBox_SetDisableClose.Name = "chkBox_SetDisableClose";
			chkBox_SetDisableClose.UseVisualStyleBackColor = true;
			chkBox_SetDisableClose.CheckedChanged += checkBox_settings_disableClose_CheckedChanged;
			// 
			// tkBar_Trans
			// 
			resources.ApplyResources(tkBar_Trans, "tkBar_Trans");
			tkBar_Trans.LargeChange = 10;
			tkBar_Trans.Maximum = 90;
			tkBar_Trans.Name = "tkBar_Trans";
			tkBar_Trans.TickFrequency = 10;
			tkBar_Trans.ValueChanged += trackBar_transparant_ValueChanged;
			// 
			// chkBox_SetScreenOn
			// 
			resources.ApplyResources(chkBox_SetScreenOn, "chkBox_SetScreenOn");
			chkBox_SetScreenOn.Name = "chkBox_SetScreenOn";
			chkBox_SetScreenOn.UseVisualStyleBackColor = true;
			chkBox_SetScreenOn.CheckedChanged += checkBox_settings_keepDisplay_CheckedChanged;
			// 
			// chkBox_SetAwake
			// 
			resources.ApplyResources(chkBox_SetAwake, "chkBox_SetAwake");
			chkBox_SetAwake.Name = "chkBox_SetAwake";
			chkBox_SetAwake.UseVisualStyleBackColor = true;
			chkBox_SetAwake.CheckedChanged += checkBox_settings_preventFromSleeping_CheckedChanged;
			// 
			// chkBox_SetNotify
			// 
			resources.ApplyResources(chkBox_SetNotify, "chkBox_SetNotify");
			chkBox_SetNotify.Name = "chkBox_SetNotify";
			chkBox_SetNotify.UseVisualStyleBackColor = true;
			chkBox_SetNotify.CheckedChanged += checkBox_settings_useNotify_CheckedChanged;
			// 
			// chkBox_SetHideToTray
			// 
			resources.ApplyResources(chkBox_SetHideToTray, "chkBox_SetHideToTray");
			chkBox_SetHideToTray.Name = "chkBox_SetHideToTray";
			chkBox_SetHideToTray.UseVisualStyleBackColor = true;
			chkBox_SetHideToTray.CheckedChanged += checkBox_settings_hideToIcon_CheckedChanged;
			// 
			// chkBox_SetShow
			// 
			resources.ApplyResources(chkBox_SetShow, "chkBox_SetShow");
			chkBox_SetShow.Name = "chkBox_SetShow";
			chkBox_SetShow.UseVisualStyleBackColor = true;
			chkBox_SetShow.CheckedChanged += checkBox_settings_showCV_CheckedChanged;
			// 
			// tabPage_Home
			// 
			tabPage_Home.Controls.Add(splitContainer0);
			resources.ApplyResources(tabPage_Home, "tabPage_Home");
			tabPage_Home.Name = "tabPage_Home";
			tabPage_Home.UseVisualStyleBackColor = true;
			// 
			// splitContainer0
			// 
			resources.ApplyResources(splitContainer0, "splitContainer0");
			splitContainer0.FixedPanel = FixedPanel.Panel1;
			splitContainer0.Name = "splitContainer0";
			// 
			// splitContainer0.Panel1
			// 
			splitContainer0.Panel1.Controls.Add(gpBox_AwardSet);
			splitContainer0.Panel1.Controls.Add(btn_Main);
			splitContainer0.Panel1.Controls.Add(gpBox_CtrlSet);
			splitContainer0.Panel1.Controls.Add(gpBox_GameSet);
			// 
			// splitContainer0.Panel2
			// 
			splitContainer0.Panel2.Controls.Add(listBox_Log);
			// 
			// gpBox_AwardSet
			// 
			gpBox_AwardSet.Controls.Add(radioBtn_AwardIgnore);
			gpBox_AwardSet.Controls.Add(radioBtn_AwardPlay);
			gpBox_AwardSet.Controls.Add(radioBtn_AwardNo);
			resources.ApplyResources(gpBox_AwardSet, "gpBox_AwardSet");
			gpBox_AwardSet.Name = "gpBox_AwardSet";
			gpBox_AwardSet.TabStop = false;
			// 
			// radioBtn_AwardIgnore
			// 
			resources.ApplyResources(radioBtn_AwardIgnore, "radioBtn_AwardIgnore");
			radioBtn_AwardIgnore.Name = "radioBtn_AwardIgnore";
			radioBtn_AwardIgnore.UseVisualStyleBackColor = true;
			radioBtn_AwardIgnore.CheckedChanged += radioBtn_home_add_CheckedChanged;
			// 
			// radioBtn_AwardPlay
			// 
			resources.ApplyResources(radioBtn_AwardPlay, "radioBtn_AwardPlay");
			radioBtn_AwardPlay.Name = "radioBtn_AwardPlay";
			radioBtn_AwardPlay.UseVisualStyleBackColor = true;
			radioBtn_AwardPlay.CheckedChanged += radioBtn_home_add_CheckedChanged;
			// 
			// radioBtn_AwardNo
			// 
			resources.ApplyResources(radioBtn_AwardNo, "radioBtn_AwardNo");
			radioBtn_AwardNo.Checked = true;
			radioBtn_AwardNo.Name = "radioBtn_AwardNo";
			radioBtn_AwardNo.TabStop = true;
			radioBtn_AwardNo.UseVisualStyleBackColor = true;
			radioBtn_AwardNo.CheckedChanged += radioBtn_home_add_CheckedChanged;
			// 
			// btn_Main
			// 
			resources.ApplyResources(btn_Main, "btn_Main");
			btn_Main.Name = "btn_Main";
			btn_Main.UseVisualStyleBackColor = true;
			btn_Main.Click += btn_home_main_Click;
			// 
			// gpBox_CtrlSet
			// 
			gpBox_CtrlSet.Controls.Add(radioBtn_CtrlInput);
			gpBox_CtrlSet.Controls.Add(radioBtn_CtrlMsg);
			resources.ApplyResources(gpBox_CtrlSet, "gpBox_CtrlSet");
			gpBox_CtrlSet.Name = "gpBox_CtrlSet";
			gpBox_CtrlSet.TabStop = false;
			// 
			// radioBtn_CtrlInput
			// 
			resources.ApplyResources(radioBtn_CtrlInput, "radioBtn_CtrlInput");
			radioBtn_CtrlInput.Name = "radioBtn_CtrlInput";
			radioBtn_CtrlInput.UseVisualStyleBackColor = true;
			radioBtn_CtrlInput.CheckedChanged += radioBtn_home_ctrl_CheckedChanged;
			// 
			// radioBtn_CtrlMsg
			// 
			resources.ApplyResources(radioBtn_CtrlMsg, "radioBtn_CtrlMsg");
			radioBtn_CtrlMsg.Checked = true;
			radioBtn_CtrlMsg.Name = "radioBtn_CtrlMsg";
			radioBtn_CtrlMsg.TabStop = true;
			radioBtn_CtrlMsg.UseVisualStyleBackColor = true;
			radioBtn_CtrlMsg.CheckedChanged += radioBtn_home_ctrl_CheckedChanged;
			// 
			// gpBox_GameSet
			// 
			gpBox_GameSet.Controls.Add(radioBtn_GameNew);
			gpBox_GameSet.Controls.Add(radioBtn_GameLast);
			resources.ApplyResources(gpBox_GameSet, "gpBox_GameSet");
			gpBox_GameSet.Name = "gpBox_GameSet";
			gpBox_GameSet.TabStop = false;
			// 
			// radioBtn_GameNew
			// 
			resources.ApplyResources(radioBtn_GameNew, "radioBtn_GameNew");
			radioBtn_GameNew.Name = "radioBtn_GameNew";
			radioBtn_GameNew.UseVisualStyleBackColor = true;
			radioBtn_GameNew.CheckedChanged += radioBtn_home_game_CheckedChanged;
			// 
			// radioBtn_GameLast
			// 
			resources.ApplyResources(radioBtn_GameLast, "radioBtn_GameLast");
			radioBtn_GameLast.Checked = true;
			radioBtn_GameLast.Name = "radioBtn_GameLast";
			radioBtn_GameLast.TabStop = true;
			radioBtn_GameLast.UseVisualStyleBackColor = true;
			radioBtn_GameLast.CheckedChanged += radioBtn_home_game_CheckedChanged;
			// 
			// listBox_Log
			// 
			resources.ApplyResources(listBox_Log, "listBox_Log");
			listBox_Log.FormattingEnabled = true;
			listBox_Log.Name = "listBox_Log";
			listBox_Log.SelectionMode = SelectionMode.None;
			listBox_Log.TabStop = false;
			listBox_Log.UseTabStops = false;
			// 
			// tabControl0
			// 
			tabControl0.Controls.Add(tabPage_Home);
			tabControl0.Controls.Add(tabPage_Set);
			resources.ApplyResources(tabControl0, "tabControl0");
			tabControl0.Name = "tabControl0";
			tabControl0.SelectedIndex = 0;
			// 
			// FormMain
			// 
			resources.ApplyResources(this, "$this");
			AutoScaleMode = AutoScaleMode.Font;
			Controls.Add(tabControl0);
			Name = "FormMain";
			Deactivate += FormMain_Deactivate;
			FormClosing += FormMain_FormClosing;
			FormClosed += FormMain_FormClosed;
			Load += FormMain_Load;
			ctxtMenu_notifyR.ResumeLayout(false);
			tabPage_Set.ResumeLayout(false);
			tabPage_Set.PerformLayout();
			((System.ComponentModel.ISupportInitialize)tkBar_Trans).EndInit();
			tabPage_Home.ResumeLayout(false);
			splitContainer0.Panel1.ResumeLayout(false);
			splitContainer0.Panel2.ResumeLayout(false);
			((System.ComponentModel.ISupportInitialize)splitContainer0).EndInit();
			splitContainer0.ResumeLayout(false);
			gpBox_AwardSet.ResumeLayout(false);
			gpBox_AwardSet.PerformLayout();
			gpBox_CtrlSet.ResumeLayout(false);
			gpBox_CtrlSet.PerformLayout();
			gpBox_GameSet.ResumeLayout(false);
			gpBox_GameSet.PerformLayout();
			tabControl0.ResumeLayout(false);
			ResumeLayout(false);
		}

		#endregion
		private System.Windows.Forms.Timer timer_main;
		private NotifyIcon notifyIcon_main;
		private ContextMenuStrip ctxtMenu_notifyR;
		private ToolStripMenuItem ctxtMenu_notifyR_exit;
		private TabPage tabPage_Set;
		private Label label_TransValue;
		private Label label_TransTitle;
		private CheckBox chkBox_SetDisableClose;
		private TrackBar tkBar_Trans;
		private CheckBox chkBox_SetScreenOn;
		private CheckBox chkBox_SetAwake;
		private CheckBox chkBox_SetNotify;
		private CheckBox chkBox_SetHideToTray;
		private CheckBox chkBox_SetShow;
		private TabPage tabPage_Home;
		private SplitContainer splitContainer0;
		private GroupBox gpBox_AwardSet;
		private RadioButton radioBtn_AwardIgnore;
		private RadioButton radioBtn_AwardPlay;
		private RadioButton radioBtn_AwardNo;
		private Button btn_Main;
		private GroupBox gpBox_CtrlSet;
		private RadioButton radioBtn_CtrlInput;
		private RadioButton radioBtn_CtrlMsg;
		private GroupBox gpBox_GameSet;
		private RadioButton radioBtn_GameNew;
		private RadioButton radioBtn_GameLast;
		private ListBox listBox_Log;
		private TabControl tabControl0;
	}
}
