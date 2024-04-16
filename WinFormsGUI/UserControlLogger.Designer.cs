namespace WinFormsGUI {
	partial class UserControlLogger {
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
			SuspendLayout();
			// 
			// listBox1
			// 
			listBox1.BackColor = SystemColors.Control;
			listBox1.BorderStyle = BorderStyle.None;
			listBox1.Dock = DockStyle.Fill;
			listBox1.DrawMode = DrawMode.OwnerDrawVariable;
			listBox1.Font = new Font("Microsoft YaHei UI", 10.5F, FontStyle.Regular, GraphicsUnit.Point, 134);
			listBox1.FormattingEnabled = true;
			listBox1.HorizontalScrollbar = true;
			listBox1.ItemHeight = 17;
			listBox1.Location = new Point(0, 0);
			listBox1.Name = "listBox1";
			listBox1.SelectionMode = SelectionMode.None;
			listBox1.Size = new Size(180, 64);
			listBox1.TabIndex = 0;
			listBox1.DrawItem += listBox1_DrawItem;
			listBox1.MeasureItem += listBox1_MeasureItem;
			// 
			// UserControlLogger
			// 
			AutoScaleDimensions = new SizeF(7F, 17F);
			AutoScaleMode = AutoScaleMode.Font;
			AutoSize = true;
			Controls.Add(listBox1);
			DoubleBuffered = true;
			MinimumSize = new Size(180, 0);
			Name = "UserControlLogger";
			Size = new Size(180, 64);
			SizeChanged += UserControlLogger_SizeChanged;
			ResumeLayout(false);
		}

		#endregion

		private ListBox listBox1;
	}
}
