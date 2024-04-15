namespace WinFormsGUI {
	partial class UserControlList {
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
			flowLayoutPanel1 = new FlowLayoutPanel();
			button_all = new Button();
			button_clear = new Button();
			contextMenuStrip1 = new ContextMenuStrip(components);
			toolStripMenuItem_Edit = new ToolStripMenuItem();
			toolStripSeparator1 = new ToolStripSeparator();
			toolStripMenuItem_All = new ToolStripMenuItem();
			toolStripMenuItem_Clear = new ToolStripMenuItem();
			contextMenuStrip1.SuspendLayout();
			SuspendLayout();
			// 
			// flowLayoutPanel1
			// 
			flowLayoutPanel1.Anchor = AnchorStyles.Top | AnchorStyles.Bottom | AnchorStyles.Left | AnchorStyles.Right;
			flowLayoutPanel1.AutoSize = true;
			flowLayoutPanel1.Location = new Point(0, 0);
			flowLayoutPanel1.Name = "flowLayoutPanel1";
			flowLayoutPanel1.Size = new Size(180, 0);
			flowLayoutPanel1.TabIndex = 3;
			// 
			// button_all
			// 
			button_all.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
			button_all.Location = new Point(4, 8);
			button_all.Name = "button_all";
			button_all.Size = new Size(85, 30);
			button_all.TabIndex = 4;
			button_all.Text = "全选";
			button_all.UseVisualStyleBackColor = true;
			button_all.Click += OnClickChooseAll;
			// 
			// button_clear
			// 
			button_clear.Anchor = AnchorStyles.Bottom | AnchorStyles.Right;
			button_clear.Location = new Point(91, 8);
			button_clear.Name = "button_clear";
			button_clear.Size = new Size(85, 30);
			button_clear.TabIndex = 5;
			button_clear.Text = "清空";
			button_clear.UseVisualStyleBackColor = true;
			button_clear.Click += OnClickClearList;
			// 
			// contextMenuStrip1
			// 
			contextMenuStrip1.Items.AddRange(new ToolStripItem[] { toolStripMenuItem_Edit, toolStripSeparator1, toolStripMenuItem_All, toolStripMenuItem_Clear });
			contextMenuStrip1.Name = "contextMenuStrip1";
			contextMenuStrip1.ShowImageMargin = false;
			contextMenuStrip1.Size = new Size(76, 76);
			// 
			// toolStripMenuItem_Edit
			// 
			toolStripMenuItem_Edit.Name = "toolStripMenuItem_Edit";
			toolStripMenuItem_Edit.Size = new Size(75, 22);
			toolStripMenuItem_Edit.Text = "编辑";
			toolStripMenuItem_Edit.Click += OnClickEditList;
			// 
			// toolStripSeparator1
			// 
			toolStripSeparator1.Name = "toolStripSeparator1";
			toolStripSeparator1.Size = new Size(72, 6);
			// 
			// toolStripMenuItem_All
			// 
			toolStripMenuItem_All.Name = "toolStripMenuItem_All";
			toolStripMenuItem_All.Size = new Size(75, 22);
			toolStripMenuItem_All.Text = "全选";
			toolStripMenuItem_All.Click += OnClickChooseAll;
			// 
			// toolStripMenuItem_Clear
			// 
			toolStripMenuItem_Clear.Name = "toolStripMenuItem_Clear";
			toolStripMenuItem_Clear.Size = new Size(75, 22);
			toolStripMenuItem_Clear.Text = "清空";
			toolStripMenuItem_Clear.Click += OnClickClearList;
			// 
			// UserControlList
			// 
			AutoScaleDimensions = new SizeF(96F, 96F);
			AutoScaleMode = AutoScaleMode.Dpi;
			ContextMenuStrip = contextMenuStrip1;
			Controls.Add(button_clear);
			Controls.Add(button_all);
			Controls.Add(flowLayoutPanel1);
			MaximumSize = new Size(180, 0);
			MinimumSize = new Size(180, 42);
			Name = "UserControlList";
			Size = new Size(180, 42);
			Load += UserControlList_Load;
			contextMenuStrip1.ResumeLayout(false);
			ResumeLayout(false);
			PerformLayout();
		}

		#endregion

		private FlowLayoutPanel flowLayoutPanel1;
		private Button button_all;
		private Button button_clear;
		private ContextMenuStrip contextMenuStrip1;
		private ToolStripMenuItem toolStripMenuItem_Edit;
		private ToolStripSeparator toolStripSeparator1;
		private ToolStripMenuItem toolStripMenuItem_All;
		private ToolStripMenuItem toolStripMenuItem_Clear;
	}
}
