namespace WinFormsGUI {
	partial class FormNew {
		/// <summary>
		/// Required designer variable.
		/// </summary>
		private System.ComponentModel.IContainer components = null;

		/// <summary>
		/// Clean up any resources being used.
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
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		private void InitializeComponent() {
			components = new System.ComponentModel.Container();
			System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormNew));
			tabControl1 = new TabControl();
			tabPage_home = new TabPage();
			userControlHome1 = new UserControlHome();
			tabPage_gSet = new TabPage();
			userControlSettings1 = new UserControlSettings();
			notifyIcon_Main = new NotifyIcon(components);
			contextMenuStrip1 = new ContextMenuStrip(components);
			toolStripMenuItem_Exit = new ToolStripMenuItem();
			tabControl1.SuspendLayout();
			tabPage_home.SuspendLayout();
			tabPage_gSet.SuspendLayout();
			contextMenuStrip1.SuspendLayout();
			SuspendLayout();
			// 
			// tabControl1
			// 
			tabControl1.Controls.Add(tabPage_home);
			tabControl1.Controls.Add(tabPage_gSet);
			tabControl1.Dock = DockStyle.Fill;
			tabControl1.Location = new Point(0, 0);
			tabControl1.Name = "tabControl1";
			tabControl1.SelectedIndex = 0;
			tabControl1.Size = new Size(784, 521);
			tabControl1.TabIndex = 0;
			// 
			// tabPage_home
			// 
			tabPage_home.BackColor = SystemColors.Control;
			tabPage_home.Controls.Add(userControlHome1);
			tabPage_home.Location = new Point(4, 26);
			tabPage_home.Name = "tabPage_home";
			tabPage_home.Padding = new Padding(3);
			tabPage_home.Size = new Size(776, 491);
			tabPage_home.TabIndex = 0;
			tabPage_home.Text = "主页";
			// 
			// userControlHome1
			// 
			userControlHome1.Dock = DockStyle.Fill;
			userControlHome1.Location = new Point(3, 3);
			userControlHome1.MinimumSize = new Size(710, 360);
			userControlHome1.Name = "userControlHome1";
			userControlHome1.Size = new Size(770, 485);
			userControlHome1.TabIndex = 0;
			// 
			// tabPage_gSet
			// 
			tabPage_gSet.Controls.Add(userControlSettings1);
			tabPage_gSet.Location = new Point(4, 26);
			tabPage_gSet.Name = "tabPage_gSet";
			tabPage_gSet.Padding = new Padding(3);
			tabPage_gSet.Size = new Size(776, 491);
			tabPage_gSet.TabIndex = 1;
			tabPage_gSet.Text = "设置";
			tabPage_gSet.UseVisualStyleBackColor = true;
			// 
			// userControlSettings1
			// 
			userControlSettings1.Dock = DockStyle.Fill;
			userControlSettings1.Location = new Point(3, 3);
			userControlSettings1.Name = "userControlSettings1";
			userControlSettings1.Size = new Size(770, 485);
			userControlSettings1.TabIndex = 0;
			// 
			// notifyIcon_Main
			// 
			notifyIcon_Main.ContextMenuStrip = contextMenuStrip1;
			notifyIcon_Main.Icon = (Icon)resources.GetObject("notifyIcon_Main.Icon");
			notifyIcon_Main.Text = "notifyIcon1";
			notifyIcon_Main.Visible = true;
			notifyIcon_Main.MouseClick += NotifyIcon_Main_MouseClick;
			// 
			// contextMenuStrip1
			// 
			contextMenuStrip1.Items.AddRange(new ToolStripItem[] { toolStripMenuItem_Exit });
			contextMenuStrip1.Name = "contextMenuStrip1";
			contextMenuStrip1.Size = new Size(101, 26);
			// 
			// toolStripMenuItem_Exit
			// 
			toolStripMenuItem_Exit.Name = "toolStripMenuItem_Exit";
			toolStripMenuItem_Exit.Size = new Size(100, 22);
			toolStripMenuItem_Exit.Text = "退出";
			toolStripMenuItem_Exit.Click += ToolStripMenuItem_Exit_Click;
			// 
			// FormNew
			// 
			AutoScaleDimensions = new SizeF(7F, 17F);
			AutoScaleMode = AutoScaleMode.Font;
			ClientSize = new Size(784, 521);
			Controls.Add(tabControl1);
			Icon = (Icon)resources.GetObject("$this.Icon");
			MinimumSize = new Size(800, 560);
			Name = "FormNew";
			Text = "DDOA";
			Deactivate += FormNew_Deactivate;
			FormClosing += FormNew_FormClosing;
			FormClosed += FormNew_FormClosed;
			Load += FormNew_Load;
			tabControl1.ResumeLayout(false);
			tabPage_home.ResumeLayout(false);
			tabPage_gSet.ResumeLayout(false);
			contextMenuStrip1.ResumeLayout(false);
			ResumeLayout(false);
		}

		#endregion

		private TabControl tabControl1;
		private TabPage tabPage_home;
		private TabPage tabPage_gSet;
		private NotifyIcon notifyIcon_Main;
		private ContextMenuStrip contextMenuStrip1;
		private ToolStripMenuItem toolStripMenuItem_Exit;
		private UserControlSettings userControlSettings1;
		private UserControlHome userControlHome1;
	}
}