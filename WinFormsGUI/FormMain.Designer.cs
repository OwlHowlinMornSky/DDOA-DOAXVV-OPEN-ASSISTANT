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
			gpBox_home_addSet = new GroupBox();
			radioBtn_home_addIgnore = new RadioButton();
			radioBtn_home_addPlay = new RadioButton();
			radioBtn_home_addNo = new RadioButton();
			btn_home_main = new Button();
			gpBox_home_ctrlSet = new GroupBox();
			radioBtn_home_ctrlInput = new RadioButton();
			radioBtn_home_ctrlMsg = new RadioButton();
			gpBox_home_gameSet = new GroupBox();
			radioBtn_home_gameNew = new RadioButton();
			radioBtn_home_gameLast = new RadioButton();
			listBox_home = new ListBox();
			tabControl_main = new TabControl();
			tabPage_main_main = new TabPage();
			panel_main_log = new Panel();
			listBox_main_log = new ListBox();
			panel_main_set = new Panel();
			panel1 = new Panel();
			groupBox1 = new GroupBox();
			radioButton1 = new RadioButton();
			radioButton2 = new RadioButton();
			panel_set_startup = new Panel();
			groupBox_set_start_wait = new GroupBox();
			label_timeLimit = new Label();
			numericUpDown1 = new NumericUpDown();
			groupBox_set_startup_plat = new GroupBox();
			radioButton_steam = new RadioButton();
			panel_main_main = new Panel();
			panel_main_task = new Panel();
			button8 = new Button();
			button7 = new Button();
			checkBox8 = new CheckBox();
			checkBox7 = new CheckBox();
			button6 = new Button();
			checkBox6 = new CheckBox();
			button5 = new Button();
			checkBox5 = new CheckBox();
			button4 = new Button();
			checkBox4 = new CheckBox();
			button3 = new Button();
			button2 = new Button();
			button1 = new Button();
			checkBox3 = new CheckBox();
			checkBox2 = new CheckBox();
			checkBox1 = new CheckBox();
			button_task_none = new Button();
			button_task_all = new Button();
			button_main_main = new Button();
			tabPage_main_home = new TabPage();
			tabPage_main_settings = new TabPage();
			label_transp_value = new Label();
			label_transparant = new Label();
			checkBox_settings_disableClose = new CheckBox();
			trackBar_transparant = new TrackBar();
			checkBox_settings_keepDisplay = new CheckBox();
			checkBox_settings_preventFromSleeping = new CheckBox();
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
			gpBox_home_addSet.SuspendLayout();
			gpBox_home_ctrlSet.SuspendLayout();
			gpBox_home_gameSet.SuspendLayout();
			tabControl_main.SuspendLayout();
			tabPage_main_main.SuspendLayout();
			panel_main_log.SuspendLayout();
			panel_main_set.SuspendLayout();
			panel1.SuspendLayout();
			groupBox1.SuspendLayout();
			panel_set_startup.SuspendLayout();
			groupBox_set_start_wait.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)numericUpDown1).BeginInit();
			groupBox_set_startup_plat.SuspendLayout();
			panel_main_main.SuspendLayout();
			panel_main_task.SuspendLayout();
			tabPage_main_home.SuspendLayout();
			tabPage_main_settings.SuspendLayout();
			((System.ComponentModel.ISupportInitialize)trackBar_transparant).BeginInit();
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
			splitContainer_Tab0_Main.Panel1.Controls.Add(gpBox_home_addSet);
			splitContainer_Tab0_Main.Panel1.Controls.Add(btn_home_main);
			splitContainer_Tab0_Main.Panel1.Controls.Add(gpBox_home_ctrlSet);
			splitContainer_Tab0_Main.Panel1.Controls.Add(gpBox_home_gameSet);
			// 
			// splitContainer_Tab0_Main.Panel2
			// 
			splitContainer_Tab0_Main.Panel2.Controls.Add(listBox_home);
			// 
			// gpBox_home_addSet
			// 
			gpBox_home_addSet.Controls.Add(radioBtn_home_addIgnore);
			gpBox_home_addSet.Controls.Add(radioBtn_home_addPlay);
			gpBox_home_addSet.Controls.Add(radioBtn_home_addNo);
			resources.ApplyResources(gpBox_home_addSet, "gpBox_home_addSet");
			gpBox_home_addSet.Name = "gpBox_home_addSet";
			gpBox_home_addSet.TabStop = false;
			// 
			// radioBtn_home_addIgnore
			// 
			resources.ApplyResources(radioBtn_home_addIgnore, "radioBtn_home_addIgnore");
			radioBtn_home_addIgnore.Name = "radioBtn_home_addIgnore";
			radioBtn_home_addIgnore.UseVisualStyleBackColor = true;
			radioBtn_home_addIgnore.CheckedChanged += radioBtn_home_add_CheckedChanged;
			// 
			// radioBtn_home_addPlay
			// 
			resources.ApplyResources(radioBtn_home_addPlay, "radioBtn_home_addPlay");
			radioBtn_home_addPlay.Name = "radioBtn_home_addPlay";
			radioBtn_home_addPlay.UseVisualStyleBackColor = true;
			radioBtn_home_addPlay.CheckedChanged += radioBtn_home_add_CheckedChanged;
			// 
			// radioBtn_home_addNo
			// 
			resources.ApplyResources(radioBtn_home_addNo, "radioBtn_home_addNo");
			radioBtn_home_addNo.Checked = true;
			radioBtn_home_addNo.Name = "radioBtn_home_addNo";
			radioBtn_home_addNo.TabStop = true;
			radioBtn_home_addNo.UseVisualStyleBackColor = true;
			radioBtn_home_addNo.CheckedChanged += radioBtn_home_add_CheckedChanged;
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
			tabControl_main.Controls.Add(tabPage_main_main);
			tabControl_main.Controls.Add(tabPage_main_home);
			tabControl_main.Controls.Add(tabPage_main_settings);
			resources.ApplyResources(tabControl_main, "tabControl_main");
			tabControl_main.Name = "tabControl_main";
			tabControl_main.SelectedIndex = 0;
			// 
			// tabPage_main_main
			// 
			tabPage_main_main.BackColor = SystemColors.Control;
			tabPage_main_main.Controls.Add(panel_main_log);
			tabPage_main_main.Controls.Add(panel_main_set);
			tabPage_main_main.Controls.Add(panel_main_main);
			resources.ApplyResources(tabPage_main_main, "tabPage_main_main");
			tabPage_main_main.Name = "tabPage_main_main";
			tabPage_main_main.SizeChanged += tabPage_main_main_SizeChanged;
			// 
			// panel_main_log
			// 
			resources.ApplyResources(panel_main_log, "panel_main_log");
			panel_main_log.Controls.Add(listBox_main_log);
			panel_main_log.Name = "panel_main_log";
			// 
			// listBox_main_log
			// 
			listBox_main_log.BackColor = SystemColors.Control;
			listBox_main_log.BorderStyle = BorderStyle.None;
			resources.ApplyResources(listBox_main_log, "listBox_main_log");
			listBox_main_log.FormattingEnabled = true;
			listBox_main_log.Name = "listBox_main_log";
			// 
			// panel_main_set
			// 
			resources.ApplyResources(panel_main_set, "panel_main_set");
			panel_main_set.Controls.Add(panel1);
			panel_main_set.Controls.Add(panel_set_startup);
			panel_main_set.Name = "panel_main_set";
			// 
			// panel1
			// 
			panel1.Controls.Add(groupBox1);
			resources.ApplyResources(panel1, "panel1");
			panel1.Name = "panel1";
			// 
			// groupBox1
			// 
			groupBox1.Controls.Add(radioButton1);
			groupBox1.Controls.Add(radioButton2);
			resources.ApplyResources(groupBox1, "groupBox1");
			groupBox1.Name = "groupBox1";
			groupBox1.TabStop = false;
			// 
			// radioButton1
			// 
			resources.ApplyResources(radioButton1, "radioButton1");
			radioButton1.Name = "radioButton1";
			radioButton1.UseVisualStyleBackColor = true;
			// 
			// radioButton2
			// 
			resources.ApplyResources(radioButton2, "radioButton2");
			radioButton2.Checked = true;
			radioButton2.Name = "radioButton2";
			radioButton2.TabStop = true;
			radioButton2.UseVisualStyleBackColor = true;
			// 
			// panel_set_startup
			// 
			panel_set_startup.Controls.Add(groupBox_set_start_wait);
			panel_set_startup.Controls.Add(groupBox_set_startup_plat);
			resources.ApplyResources(panel_set_startup, "panel_set_startup");
			panel_set_startup.Name = "panel_set_startup";
			// 
			// groupBox_set_start_wait
			// 
			groupBox_set_start_wait.Controls.Add(label_timeLimit);
			groupBox_set_start_wait.Controls.Add(numericUpDown1);
			resources.ApplyResources(groupBox_set_start_wait, "groupBox_set_start_wait");
			groupBox_set_start_wait.Name = "groupBox_set_start_wait";
			groupBox_set_start_wait.TabStop = false;
			// 
			// label_timeLimit
			// 
			resources.ApplyResources(label_timeLimit, "label_timeLimit");
			label_timeLimit.Name = "label_timeLimit";
			// 
			// numericUpDown1
			// 
			resources.ApplyResources(numericUpDown1, "numericUpDown1");
			numericUpDown1.Name = "numericUpDown1";
			// 
			// groupBox_set_startup_plat
			// 
			groupBox_set_startup_plat.Controls.Add(radioButton_steam);
			resources.ApplyResources(groupBox_set_startup_plat, "groupBox_set_startup_plat");
			groupBox_set_startup_plat.Name = "groupBox_set_startup_plat";
			groupBox_set_startup_plat.TabStop = false;
			// 
			// radioButton_steam
			// 
			resources.ApplyResources(radioButton_steam, "radioButton_steam");
			radioButton_steam.Checked = true;
			radioButton_steam.Name = "radioButton_steam";
			radioButton_steam.TabStop = true;
			radioButton_steam.UseVisualStyleBackColor = true;
			// 
			// panel_main_main
			// 
			resources.ApplyResources(panel_main_main, "panel_main_main");
			panel_main_main.Controls.Add(panel_main_task);
			panel_main_main.Controls.Add(button_main_main);
			panel_main_main.Name = "panel_main_main";
			// 
			// panel_main_task
			// 
			resources.ApplyResources(panel_main_task, "panel_main_task");
			panel_main_task.BorderStyle = BorderStyle.FixedSingle;
			panel_main_task.Controls.Add(button8);
			panel_main_task.Controls.Add(button7);
			panel_main_task.Controls.Add(checkBox8);
			panel_main_task.Controls.Add(checkBox7);
			panel_main_task.Controls.Add(button6);
			panel_main_task.Controls.Add(checkBox6);
			panel_main_task.Controls.Add(button5);
			panel_main_task.Controls.Add(checkBox5);
			panel_main_task.Controls.Add(button4);
			panel_main_task.Controls.Add(checkBox4);
			panel_main_task.Controls.Add(button3);
			panel_main_task.Controls.Add(button2);
			panel_main_task.Controls.Add(button1);
			panel_main_task.Controls.Add(checkBox3);
			panel_main_task.Controls.Add(checkBox2);
			panel_main_task.Controls.Add(checkBox1);
			panel_main_task.Controls.Add(button_task_none);
			panel_main_task.Controls.Add(button_task_all);
			panel_main_task.Name = "panel_main_task";
			// 
			// button8
			// 
			resources.ApplyResources(button8, "button8");
			button8.Name = "button8";
			button8.UseVisualStyleBackColor = true;
			button8.Click += button8_Click;
			// 
			// button7
			// 
			resources.ApplyResources(button7, "button7");
			button7.Name = "button7";
			button7.UseVisualStyleBackColor = true;
			button7.Click += button7_Click;
			// 
			// checkBox8
			// 
			resources.ApplyResources(checkBox8, "checkBox8");
			checkBox8.Name = "checkBox8";
			checkBox8.UseVisualStyleBackColor = true;
			// 
			// checkBox7
			// 
			resources.ApplyResources(checkBox7, "checkBox7");
			checkBox7.Name = "checkBox7";
			checkBox7.UseVisualStyleBackColor = true;
			// 
			// button6
			// 
			resources.ApplyResources(button6, "button6");
			button6.Name = "button6";
			button6.UseVisualStyleBackColor = true;
			button6.Click += button6_Click;
			// 
			// checkBox6
			// 
			resources.ApplyResources(checkBox6, "checkBox6");
			checkBox6.Name = "checkBox6";
			checkBox6.UseVisualStyleBackColor = true;
			// 
			// button5
			// 
			resources.ApplyResources(button5, "button5");
			button5.Name = "button5";
			button5.UseVisualStyleBackColor = true;
			button5.Click += button5_Click;
			// 
			// checkBox5
			// 
			resources.ApplyResources(checkBox5, "checkBox5");
			checkBox5.Name = "checkBox5";
			checkBox5.UseVisualStyleBackColor = true;
			// 
			// button4
			// 
			resources.ApplyResources(button4, "button4");
			button4.Name = "button4";
			button4.UseVisualStyleBackColor = true;
			button4.Click += button4_Click;
			// 
			// checkBox4
			// 
			resources.ApplyResources(checkBox4, "checkBox4");
			checkBox4.Name = "checkBox4";
			checkBox4.UseVisualStyleBackColor = true;
			// 
			// button3
			// 
			resources.ApplyResources(button3, "button3");
			button3.Name = "button3";
			button3.UseVisualStyleBackColor = true;
			button3.Click += button3_Click;
			// 
			// button2
			// 
			resources.ApplyResources(button2, "button2");
			button2.Name = "button2";
			button2.UseVisualStyleBackColor = true;
			button2.Click += button2_Click;
			// 
			// button1
			// 
			resources.ApplyResources(button1, "button1");
			button1.Name = "button1";
			button1.UseVisualStyleBackColor = true;
			button1.Click += button1_Click;
			// 
			// checkBox3
			// 
			resources.ApplyResources(checkBox3, "checkBox3");
			checkBox3.Name = "checkBox3";
			checkBox3.UseVisualStyleBackColor = true;
			// 
			// checkBox2
			// 
			resources.ApplyResources(checkBox2, "checkBox2");
			checkBox2.Name = "checkBox2";
			checkBox2.UseVisualStyleBackColor = true;
			// 
			// checkBox1
			// 
			resources.ApplyResources(checkBox1, "checkBox1");
			checkBox1.Name = "checkBox1";
			checkBox1.UseVisualStyleBackColor = true;
			// 
			// button_task_none
			// 
			resources.ApplyResources(button_task_none, "button_task_none");
			button_task_none.Name = "button_task_none";
			button_task_none.UseVisualStyleBackColor = true;
			button_task_none.Click += button_task_none_Click;
			// 
			// button_task_all
			// 
			resources.ApplyResources(button_task_all, "button_task_all");
			button_task_all.Name = "button_task_all";
			button_task_all.UseVisualStyleBackColor = true;
			button_task_all.Click += button_task_all_Click;
			// 
			// button_main_main
			// 
			resources.ApplyResources(button_main_main, "button_main_main");
			button_main_main.Name = "button_main_main";
			button_main_main.UseVisualStyleBackColor = true;
			button_main_main.Click += button_main_main_Click;
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
			tabPage_main_settings.Controls.Add(label_transp_value);
			tabPage_main_settings.Controls.Add(label_transparant);
			tabPage_main_settings.Controls.Add(checkBox_settings_disableClose);
			tabPage_main_settings.Controls.Add(trackBar_transparant);
			tabPage_main_settings.Controls.Add(checkBox_settings_keepDisplay);
			tabPage_main_settings.Controls.Add(checkBox_settings_preventFromSleeping);
			tabPage_main_settings.Controls.Add(checkBox_settings_useNotify);
			tabPage_main_settings.Controls.Add(checkBox_settings_hideToIcon);
			tabPage_main_settings.Controls.Add(checkBox_settings_showCV);
			resources.ApplyResources(tabPage_main_settings, "tabPage_main_settings");
			tabPage_main_settings.Name = "tabPage_main_settings";
			tabPage_main_settings.UseVisualStyleBackColor = true;
			// 
			// label_transp_value
			// 
			resources.ApplyResources(label_transp_value, "label_transp_value");
			label_transp_value.Name = "label_transp_value";
			label_transp_value.SizeChanged += label_transp_value_SizeChanged;
			// 
			// label_transparant
			// 
			resources.ApplyResources(label_transparant, "label_transparant");
			label_transparant.Name = "label_transparant";
			// 
			// checkBox_settings_disableClose
			// 
			resources.ApplyResources(checkBox_settings_disableClose, "checkBox_settings_disableClose");
			checkBox_settings_disableClose.Name = "checkBox_settings_disableClose";
			checkBox_settings_disableClose.UseVisualStyleBackColor = true;
			checkBox_settings_disableClose.CheckedChanged += checkBox_settings_disableClose_CheckedChanged;
			// 
			// trackBar_transparant
			// 
			resources.ApplyResources(trackBar_transparant, "trackBar_transparant");
			trackBar_transparant.LargeChange = 10;
			trackBar_transparant.Maximum = 90;
			trackBar_transparant.Name = "trackBar_transparant";
			trackBar_transparant.TickFrequency = 10;
			trackBar_transparant.ValueChanged += trackBar_transparant_ValueChanged;
			// 
			// checkBox_settings_keepDisplay
			// 
			resources.ApplyResources(checkBox_settings_keepDisplay, "checkBox_settings_keepDisplay");
			checkBox_settings_keepDisplay.Name = "checkBox_settings_keepDisplay";
			checkBox_settings_keepDisplay.UseVisualStyleBackColor = true;
			checkBox_settings_keepDisplay.CheckedChanged += checkBox_settings_keepDisplay_CheckedChanged;
			// 
			// checkBox_settings_preventFromSleeping
			// 
			resources.ApplyResources(checkBox_settings_preventFromSleeping, "checkBox_settings_preventFromSleeping");
			checkBox_settings_preventFromSleeping.Name = "checkBox_settings_preventFromSleeping";
			checkBox_settings_preventFromSleeping.UseVisualStyleBackColor = true;
			checkBox_settings_preventFromSleeping.CheckedChanged += checkBox_settings_preventFromSleeping_CheckedChanged;
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
			gpBox_home_addSet.ResumeLayout(false);
			gpBox_home_addSet.PerformLayout();
			gpBox_home_ctrlSet.ResumeLayout(false);
			gpBox_home_ctrlSet.PerformLayout();
			gpBox_home_gameSet.ResumeLayout(false);
			gpBox_home_gameSet.PerformLayout();
			tabControl_main.ResumeLayout(false);
			tabPage_main_main.ResumeLayout(false);
			panel_main_log.ResumeLayout(false);
			panel_main_set.ResumeLayout(false);
			panel1.ResumeLayout(false);
			groupBox1.ResumeLayout(false);
			groupBox1.PerformLayout();
			panel_set_startup.ResumeLayout(false);
			groupBox_set_start_wait.ResumeLayout(false);
			groupBox_set_start_wait.PerformLayout();
			((System.ComponentModel.ISupportInitialize)numericUpDown1).EndInit();
			groupBox_set_startup_plat.ResumeLayout(false);
			groupBox_set_startup_plat.PerformLayout();
			panel_main_main.ResumeLayout(false);
			panel_main_task.ResumeLayout(false);
			panel_main_task.PerformLayout();
			tabPage_main_home.ResumeLayout(false);
			tabPage_main_settings.ResumeLayout(false);
			tabPage_main_settings.PerformLayout();
			((System.ComponentModel.ISupportInitialize)trackBar_transparant).EndInit();
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
		private CheckBox checkBox_settings_keepDisplay;
		private CheckBox checkBox_settings_preventFromSleeping;
		private CheckBox checkBox_settings_disableClose;
		private GroupBox gpBox_home_addSet;
		private RadioButton radioBtn_home_addIgnore;
		private RadioButton radioBtn_home_addPlay;
		private RadioButton radioBtn_home_addNo;
		private TabPage tabPage_main_main;
		private Panel panel_main_log;
		private ListBox listBox_main_log;
		private Panel panel_main_set;
		private Panel panel_main_main;
		private Button button_main_main;
		private Panel panel_main_task;
		private Button button_task_none;
		private Button button_task_all;
		private CheckBox checkBox3;
		private CheckBox checkBox2;
		private CheckBox checkBox1;
		private Panel panel_set_startup;
		private Button button3;
		private Button button2;
		private Button button1;
		private Label label_transp_value;
		private Label label_transparant;
		private TrackBar trackBar_transparant;
		private CheckBox checkBox6;
		private Button button5;
		private CheckBox checkBox5;
		private Button button4;
		private CheckBox checkBox4;
		private CheckBox checkBox8;
		private CheckBox checkBox7;
		private Button button6;
		private Button button8;
		private Button button7;
		private GroupBox groupBox_set_start_wait;
		private GroupBox groupBox_set_startup_plat;
		private RadioButton radioButton_steam;
		private Label label_timeLimit;
		private NumericUpDown numericUpDown1;
		private Panel panel1;
		private GroupBox groupBox1;
		private RadioButton radioButton1;
		private RadioButton radioButton2;
	}
}
