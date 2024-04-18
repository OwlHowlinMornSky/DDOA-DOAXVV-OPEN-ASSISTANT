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
			components = new System.ComponentModel.Container();
			listBox1 = new ListBox();
			contextMenuStrip1 = new ContextMenuStrip(components);
			toolStripMenuItem_LogClr = new ToolStripMenuItem();
			contextMenuStrip1.SuspendLayout();
			SuspendLayout();
			// 
			// listBox1
			// 
			listBox1.BackColor = SystemColors.Control;
			listBox1.BorderStyle = BorderStyle.None;
			listBox1.Dock = DockStyle.Fill;
			listBox1.DrawMode = DrawMode.OwnerDrawVariable;
			listBox1.FormattingEnabled = true;
			listBox1.HorizontalScrollbar = true;
			listBox1.ItemHeight = 17;
			listBox1.Location = new Point(0, 0);
			listBox1.Name = "listBox1";
			listBox1.SelectionMode = SelectionMode.None;
			listBox1.Size = new Size(180, 74);
			listBox1.TabIndex = 0;
			listBox1.DrawItem += ListBox1_DrawItem;
			listBox1.MeasureItem += ListBox1_MeasureItem;
			// 
			// contextMenuStrip1
			// 
			contextMenuStrip1.Items.AddRange(new ToolStripItem[] { toolStripMenuItem_LogClr });
			contextMenuStrip1.Name = "contextMenuStrip1";
			contextMenuStrip1.ShowImageMargin = false;
			contextMenuStrip1.Size = new Size(156, 48);
			// 
			// toolStripMenuItem_LogClr
			// 
			toolStripMenuItem_LogClr.Name = "toolStripMenuItem_LogClr";
			toolStripMenuItem_LogClr.Size = new Size(155, 22);
			toolStripMenuItem_LogClr.Text = "清空";
			toolStripMenuItem_LogClr.Click += ToolStripMenuItem_LogClr_Click;
			// 
			// UserControlLogger
			// 
			AutoScaleDimensions = new SizeF(7F, 17F);
			AutoScaleMode = AutoScaleMode.Font;
			AutoSize = true;
			ContextMenuStrip = contextMenuStrip1;
			Controls.Add(listBox1);
			MinimumSize = new Size(180, 0);
			Name = "UserControlLogger";
			Size = new Size(180, 74);
			SizeChanged += UserControlLogger_SizeChanged;
			contextMenuStrip1.ResumeLayout(false);
			ResumeLayout(false);
		}

		#endregion

		private ListBox listBox1;
		private ContextMenuStrip contextMenuStrip1;
		private ToolStripMenuItem toolStripMenuItem_LogClr;
	}
}
