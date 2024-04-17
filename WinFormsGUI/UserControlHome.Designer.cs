namespace WinFormsGUI {
	partial class UserControlHome {
		/// <summary> 
		/// 必需的设计器变量。
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary> 
		/// 清理所有正在使用的资源。
		/// </summary>
		/// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
		protected override void Dispose(bool disposing) {
			if (disposing && (components != null)) {
				components.Dispose();
			}
			base.Dispose(disposing);
		}

		#region 组件设计器生成的代码

		/// <summary> 
		/// 设计器支持所需的方法 - 不要修改
		/// 使用代码编辑器修改此方法的内容。
		/// </summary>
		private void InitializeComponent() {
			components = new System.ComponentModel.Container();
			tableLayoutPanel_Main = new TableLayoutPanel();
			panel_Settings = new Panel();
			userControlLogger = new UserControlLogger();
			panel_leftCtrl = new Panel();
			button_Main = new Button();
			userControlList = new UserControlList();
			timer_Main = new System.Windows.Forms.Timer(components);
			tableLayoutPanel_Main.SuspendLayout();
			panel_leftCtrl.SuspendLayout();
			SuspendLayout();
			// 
			// tableLayoutPanel_Main
			// 
			tableLayoutPanel_Main.ColumnCount = 3;
			tableLayoutPanel_Main.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 40F));
			tableLayoutPanel_Main.ColumnStyles.Add(new ColumnStyle());
			tableLayoutPanel_Main.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 60F));
			tableLayoutPanel_Main.Controls.Add(panel_Settings, 1, 0);
			tableLayoutPanel_Main.Controls.Add(userControlLogger, 2, 0);
			tableLayoutPanel_Main.Controls.Add(panel_leftCtrl, 0, 0);
			tableLayoutPanel_Main.Dock = DockStyle.Fill;
			tableLayoutPanel_Main.Location = new Point(0, 0);
			tableLayoutPanel_Main.MinimumSize = new Size(700, 0);
			tableLayoutPanel_Main.Name = "tableLayoutPanel_Main";
			tableLayoutPanel_Main.RowCount = 1;
			tableLayoutPanel_Main.RowStyles.Add(new RowStyle(SizeType.Percent, 100F));
			tableLayoutPanel_Main.Size = new Size(710, 360);
			tableLayoutPanel_Main.TabIndex = 3;
			// 
			// panel_Settings
			// 
			panel_Settings.Dock = DockStyle.Fill;
			panel_Settings.Location = new Point(200, 3);
			panel_Settings.MaximumSize = new Size(210, 0);
			panel_Settings.MinimumSize = new Size(210, 0);
			panel_Settings.Name = "panel_Settings";
			panel_Settings.Size = new Size(210, 354);
			panel_Settings.TabIndex = 2;
			// 
			// userControlLogger
			// 
			userControlLogger.AutoSize = true;
			userControlLogger.BackColor = Color.RosyBrown;
			userControlLogger.Dock = DockStyle.Fill;
			userControlLogger.Location = new Point(416, 3);
			userControlLogger.MinimumSize = new Size(180, 0);
			userControlLogger.Name = "userControlLogger";
			userControlLogger.Size = new Size(291, 354);
			userControlLogger.TabIndex = 3;
			// 
			// panel_leftCtrl
			// 
			panel_leftCtrl.Controls.Add(button_Main);
			panel_leftCtrl.Controls.Add(userControlList);
			panel_leftCtrl.Dock = DockStyle.Fill;
			panel_leftCtrl.Location = new Point(3, 3);
			panel_leftCtrl.Name = "panel_leftCtrl";
			panel_leftCtrl.Size = new Size(191, 354);
			panel_leftCtrl.TabIndex = 4;
			panel_leftCtrl.SizeChanged += Panel_LeftCtrl_SizeChanged;
			// 
			// button_Main
			// 
			button_Main.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
			button_Main.Location = new Point(3, 302);
			button_Main.Name = "button_Main";
			button_Main.Size = new Size(92, 49);
			button_Main.TabIndex = 1;
			button_Main.Text = "MainButton";
			button_Main.UseVisualStyleBackColor = true;
			button_Main.Click += Button_Main_Click;
			// 
			// userControlList
			// 
			userControlList.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
			userControlList.BorderStyle = BorderStyle.FixedSingle;
			userControlList.Location = new Point(0, 0);
			userControlList.MaximumSize = new Size(180, 0);
			userControlList.MinimumSize = new Size(180, 42);
			userControlList.Name = "userControlList";
			userControlList.Size = new Size(180, 296);
			userControlList.TabIndex = 0;
			// 
			// timer_Main
			// 
			timer_Main.Interval = 60;
			timer_Main.Tick += Timer_Main_Tick;
			// 
			// UserControlHome
			// 
			AutoScaleDimensions = new SizeF(7F, 17F);
			AutoScaleMode = AutoScaleMode.Font;
			Controls.Add(tableLayoutPanel_Main);
			MinimumSize = new Size(710, 360);
			Name = "UserControlHome";
			Size = new Size(710, 360);
			Load += UserControlHome_Load;
			tableLayoutPanel_Main.ResumeLayout(false);
			tableLayoutPanel_Main.PerformLayout();
			panel_leftCtrl.ResumeLayout(false);
			ResumeLayout(false);
		}

		#endregion

		private TableLayoutPanel tableLayoutPanel_Main;
		private Panel panel_Settings;
		private UserControlLogger userControlLogger;
		private Panel panel_leftCtrl;
		private Button button_Main;
		private UserControlList userControlList;
		private System.Windows.Forms.Timer timer_Main;
	}
}
