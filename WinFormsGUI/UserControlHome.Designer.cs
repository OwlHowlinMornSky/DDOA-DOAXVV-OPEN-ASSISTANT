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
			tableLayoutPanel1 = new TableLayoutPanel();
			panel1 = new Panel();
			userControlLogger1 = new UserControlLogger();
			panel2 = new Panel();
			button1 = new Button();
			userControlList1 = new UserControlList();
			tableLayoutPanel1.SuspendLayout();
			panel2.SuspendLayout();
			SuspendLayout();
			// 
			// tableLayoutPanel1
			// 
			tableLayoutPanel1.ColumnCount = 3;
			tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 40F));
			tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle());
			tableLayoutPanel1.ColumnStyles.Add(new ColumnStyle(SizeType.Percent, 60F));
			tableLayoutPanel1.Controls.Add(panel1, 1, 0);
			tableLayoutPanel1.Controls.Add(userControlLogger1, 2, 0);
			tableLayoutPanel1.Controls.Add(panel2, 0, 0);
			tableLayoutPanel1.Dock = DockStyle.Fill;
			tableLayoutPanel1.Location = new Point(0, 0);
			tableLayoutPanel1.MinimumSize = new Size(700, 0);
			tableLayoutPanel1.Name = "tableLayoutPanel1";
			tableLayoutPanel1.RowCount = 1;
			tableLayoutPanel1.RowStyles.Add(new RowStyle(SizeType.Percent, 100F));
			tableLayoutPanel1.Size = new Size(710, 360);
			tableLayoutPanel1.TabIndex = 3;
			// 
			// panel1
			// 
			panel1.Dock = DockStyle.Fill;
			panel1.Location = new Point(200, 3);
			panel1.MaximumSize = new Size(210, 0);
			panel1.MinimumSize = new Size(210, 0);
			panel1.Name = "panel1";
			panel1.Size = new Size(210, 354);
			panel1.TabIndex = 2;
			// 
			// userControlLogger1
			// 
			userControlLogger1.AutoSize = true;
			userControlLogger1.BackColor = Color.RosyBrown;
			userControlLogger1.Dock = DockStyle.Fill;
			userControlLogger1.Location = new Point(416, 3);
			userControlLogger1.MinimumSize = new Size(180, 0);
			userControlLogger1.Name = "userControlLogger1";
			userControlLogger1.Size = new Size(291, 354);
			userControlLogger1.TabIndex = 3;
			// 
			// panel2
			// 
			panel2.Controls.Add(button1);
			panel2.Controls.Add(userControlList1);
			panel2.Dock = DockStyle.Fill;
			panel2.Location = new Point(3, 3);
			panel2.Name = "panel2";
			panel2.Size = new Size(191, 354);
			panel2.TabIndex = 4;
			panel2.SizeChanged += panel2_SizeChanged;
			// 
			// button1
			// 
			button1.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
			button1.Location = new Point(3, 302);
			button1.Name = "button1";
			button1.Size = new Size(92, 49);
			button1.TabIndex = 1;
			button1.Text = "MainButton";
			button1.UseVisualStyleBackColor = true;
			button1.Click += button1_Click;
			// 
			// userControlList1
			// 
			userControlList1.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
			userControlList1.BorderStyle = BorderStyle.FixedSingle;
			userControlList1.Location = new Point(0, 0);
			userControlList1.MaximumSize = new Size(180, 0);
			userControlList1.MinimumSize = new Size(180, 42);
			userControlList1.Name = "userControlList1";
			userControlList1.Size = new Size(180, 296);
			userControlList1.TabIndex = 0;
			// 
			// UserControlHome
			// 
			AutoScaleDimensions = new SizeF(7F, 17F);
			AutoScaleMode = AutoScaleMode.Font;
			Controls.Add(tableLayoutPanel1);
			DoubleBuffered = true;
			MinimumSize = new Size(710, 360);
			Name = "UserControlHome";
			Size = new Size(710, 360);
			Load += UserControlHome_Load;
			tableLayoutPanel1.ResumeLayout(false);
			tableLayoutPanel1.PerformLayout();
			panel2.ResumeLayout(false);
			ResumeLayout(false);
		}

		#endregion

		private TableLayoutPanel tableLayoutPanel1;
		private Panel panel1;
		private UserControlLogger userControlLogger1;
		private Panel panel2;
		private Button button1;
		private UserControlList userControlList1;
	}
}
