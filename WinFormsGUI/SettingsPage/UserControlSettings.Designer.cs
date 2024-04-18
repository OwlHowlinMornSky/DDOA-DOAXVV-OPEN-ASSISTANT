namespace WinFormsGUI {
	partial class UserControlSettings {
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
			listBox1 = new ListBox();
			panel1 = new Panel();
			SuspendLayout();
			// 
			// listBox1
			// 
			listBox1.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left;
			listBox1.Font = new Font("Microsoft YaHei UI", 12F, FontStyle.Regular, GraphicsUnit.Point, 134);
			listBox1.FormattingEnabled = true;
			listBox1.IntegralHeight = false;
			listBox1.ItemHeight = 21;
			listBox1.Items.AddRange(new object[] { "界面设置", "任务设置", "控制设置" });
			listBox1.Location = new Point(3, 3);
			listBox1.Name = "listBox1";
			listBox1.Size = new Size(185, 403);
			listBox1.TabIndex = 0;
			listBox1.SelectedIndexChanged += ListBox1_SelectedIndexChanged;
			// 
			// panel1
			// 
			panel1.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
			panel1.BorderStyle = BorderStyle.FixedSingle;
			panel1.Location = new Point(194, 3);
			panel1.Name = "panel1";
			panel1.Size = new Size(377, 403);
			panel1.TabIndex = 1;
			// 
			// UserControlSettings
			// 
			AutoScaleDimensions = new SizeF(7F, 17F);
			AutoScaleMode = AutoScaleMode.Font;
			Controls.Add(panel1);
			Controls.Add(listBox1);
			Name = "UserControlSettings";
			Size = new Size(574, 409);
			Load += UserControlSettings_Load;
			ResumeLayout(false);
		}

		#endregion

		private ListBox listBox1;
		private Panel panel1;
	}
}
