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
			tableLayoutPanel1 = new TableLayoutPanel();
			userControlList = new UserControlList();
			panel1 = new Panel();
			button_Resume = new Button();
			button_Main = new Button();
			tableLayoutPanel_Main.SuspendLayout();
			tableLayoutPanel1.SuspendLayout();
			panel1.SuspendLayout();
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
			tableLayoutPanel_Main.Controls.Add(tableLayoutPanel1, 0, 0);
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
			// tableLayoutPanel1
			// 
			tableLayoutPanel1.ColumnCount = 3;
			tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 50F));
			tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Absolute, 185F));
			tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 50F));
			tableLayoutPanel1.Controls.Add(userControlList, 1, 0);
			tableLayoutPanel1.Controls.Add(panel1, 1, 1);
			tableLayoutPanel1.Dock = DockStyle.Fill;
			tableLayoutPanel1.Location = new Point(3, 3);
			tableLayoutPanel1.Name = "tableLayoutPanel1";
			tableLayoutPanel1.RowCount = 2;
			tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 100F));
			tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Absolute, 60F));
			tableLayoutPanel1.Size = new Size(191, 354);
			tableLayoutPanel1.TabIndex = 4;
			// 
			// userControlList
			// 
			userControlList.BorderStyle = BorderStyle.FixedSingle;
			userControlList.Dock = DockStyle.Fill;
			userControlList.Location = new Point(6, 3);
			userControlList.MaximumSize = new Size(180, 999999999);
			userControlList.MinimumSize = new Size(180, 180);
			userControlList.Name = "userControlList";
			userControlList.Size = new Size(180, 288);
			userControlList.TabIndex = 2;
			// 
			// panel1
			// 
			panel1.Controls.Add(button_Resume);
			panel1.Controls.Add(button_Main);
			panel1.Dock = DockStyle.Fill;
			panel1.Location = new Point(6, 297);
			panel1.Name = "panel1";
			panel1.Size = new Size(179, 54);
			panel1.TabIndex = 3;
			// 
			// button_Resume
			// 
			button_Resume.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
			button_Resume.Location = new Point(91, 3);
			button_Resume.Name = "button_Resume";
			button_Resume.Size = new Size(85, 49);
			button_Resume.TabIndex = 3;
			button_Resume.Text = "继续";
			button_Resume.UseVisualStyleBackColor = true;
			button_Resume.Click += Button_Resume_Click;
			// 
			// button_Main
			// 
			button_Main.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
			button_Main.Location = new Point(4, 3);
			button_Main.Name = "button_Main";
			button_Main.Size = new Size(85, 49);
			button_Main.TabIndex = 1;
			button_Main.Text = "MainButton";
			button_Main.UseVisualStyleBackColor = true;
			button_Main.Click += Button_Main_Click;
			// 
			// UserControlHome
			// 
			AutoScaleMode = AutoScaleMode.Inherit;
			Controls.Add(tableLayoutPanel_Main);
			MinimumSize = new Size(710, 360);
			Name = "UserControlHome";
			Size = new Size(710, 360);
			Load += UserControlHome_Load;
			tableLayoutPanel_Main.ResumeLayout(false);
			tableLayoutPanel_Main.PerformLayout();
			tableLayoutPanel1.ResumeLayout(false);
			panel1.ResumeLayout(false);
			ResumeLayout(false);
		}

		#endregion

		private TableLayoutPanel tableLayoutPanel_Main;
		private Panel panel_Settings;
		private UserControlLogger userControlLogger;
		private Button button_Main;
		private UserControlList userControlList;
		private Button button_Resume;
		private TableLayoutPanel tableLayoutPanel1;
		private Panel panel1;
	}
}
