namespace WinFormsGUI {
	partial class UserControlSetForDaily {
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
			checkBox_check = new CheckBox();
			checkBox_camShot = new CheckBox();
			SuspendLayout();
			// 
			// checkBox_check
			// 
			checkBox_check.AutoSize = true;
			checkBox_check.Location = new Point(3, 3);
			checkBox_check.Name = "checkBox_check";
			checkBox_check.Size = new Size(75, 21);
			checkBox_check.TabIndex = 0;
			checkBox_check.Text = "每日签到";
			checkBox_check.UseVisualStyleBackColor = true;
			checkBox_check.CheckedChanged += CheckBox_check_CheckedChanged;
			// 
			// checkBox_camShot
			// 
			checkBox_camShot.AutoSize = true;
			checkBox_camShot.Location = new Point(3, 30);
			checkBox_camShot.Name = "checkBox_camShot";
			checkBox_camShot.Size = new Size(75, 21);
			checkBox_camShot.TabIndex = 1;
			checkBox_camShot.Text = "每日拍摄";
			checkBox_camShot.UseVisualStyleBackColor = true;
			checkBox_camShot.CheckedChanged += CheckBox_camShot_CheckedChanged;
			// 
			// UserControlSetForDaily
			// 
			AutoScaleDimensions = new SizeF(7F, 17F);
			AutoScaleMode = AutoScaleMode.Font;
			Controls.Add(checkBox_camShot);
			Controls.Add(checkBox_check);
			Name = "UserControlSetForDaily";
			Load += UserControlSetForDaily_Load;
			ResumeLayout(false);
			PerformLayout();
		}

		#endregion

		private CheckBox checkBox_check;
		private CheckBox checkBox_camShot;
	}
}
