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
			flowLayoutPanel1 = new FlowLayoutPanel();
			SuspendLayout();
			// 
			// flowLayoutPanel1
			// 
			flowLayoutPanel1.Dock = DockStyle.Fill;
			flowLayoutPanel1.Location = new Point(0, 0);
			flowLayoutPanel1.Name = "flowLayoutPanel1";
			flowLayoutPanel1.Size = new Size(150, 150);
			flowLayoutPanel1.TabIndex = 3;
			// 
			// UserControlList
			// 
			AutoScaleDimensions = new SizeF(7F, 17F);
			AutoScaleMode = AutoScaleMode.Font;
			Controls.Add(flowLayoutPanel1);
			Name = "UserControlList";
			ResumeLayout(false);
		}

		#endregion

		private FlowLayoutPanel flowLayoutPanel1;
	}
}
