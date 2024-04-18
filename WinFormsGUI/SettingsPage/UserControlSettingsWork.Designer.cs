namespace WinFormsGUI.SettingsPage {
	partial class UserControlSettingsWork {
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
			chkBox_SetScreenOn = new CheckBox();
			chkBox_SetAwake = new CheckBox();
			chkBox_SetShow = new CheckBox();
			SuspendLayout();
			// 
			// chkBox_SetScreenOn
			// 
			chkBox_SetScreenOn.AutoSize = true;
			chkBox_SetScreenOn.Enabled = false;
			chkBox_SetScreenOn.ImeMode = ImeMode.NoControl;
			chkBox_SetScreenOn.Location = new Point(168, 3);
			chkBox_SetScreenOn.Name = "chkBox_SetScreenOn";
			chkBox_SetScreenOn.Size = new Size(123, 21);
			chkBox_SetScreenOn.TabIndex = 18;
			chkBox_SetScreenOn.Text = "同时保持屏幕显示";
			chkBox_SetScreenOn.UseVisualStyleBackColor = true;
			chkBox_SetScreenOn.CheckedChanged += ChkBox_SetScreenOn_CheckedChanged;
			// 
			// chkBox_SetAwake
			// 
			chkBox_SetAwake.AutoSize = true;
			chkBox_SetAwake.ImeMode = ImeMode.NoControl;
			chkBox_SetAwake.Location = new Point(3, 3);
			chkBox_SetAwake.Name = "chkBox_SetAwake";
			chkBox_SetAwake.Size = new Size(159, 21);
			chkBox_SetAwake.TabIndex = 17;
			chkBox_SetAwake.Text = "执行任务时阻止系统睡眠";
			chkBox_SetAwake.UseVisualStyleBackColor = true;
			chkBox_SetAwake.CheckedChanged += ChkBox_SetAwake_CheckedChanged;
			// 
			// chkBox_SetShow
			// 
			chkBox_SetShow.Anchor = AnchorStyles.Bottom | AnchorStyles.Left;
			chkBox_SetShow.AutoSize = true;
			chkBox_SetShow.ImeMode = ImeMode.NoControl;
			chkBox_SetShow.Location = new Point(3, 322);
			chkBox_SetShow.Name = "chkBox_SetShow";
			chkBox_SetShow.Size = new Size(143, 21);
			chkBox_SetShow.TabIndex = 16;
			chkBox_SetShow.Text = "[调试]显示截取的图像";
			chkBox_SetShow.UseVisualStyleBackColor = true;
			chkBox_SetShow.Visible = false;
			chkBox_SetShow.CheckedChanged += ChkBox_SetShow_CheckedChanged;
			// 
			// UserControlSettingsWork
			// 
			AutoScaleDimensions = new SizeF(7F, 17F);
			AutoScaleMode = AutoScaleMode.Font;
			Controls.Add(chkBox_SetScreenOn);
			Controls.Add(chkBox_SetAwake);
			Controls.Add(chkBox_SetShow);
			Name = "UserControlSettingsWork";
			Size = new Size(337, 346);
			Load += UserControlSettingsWork_Load;
			ResumeLayout(false);
			PerformLayout();
		}

		#endregion

		private CheckBox chkBox_SetScreenOn;
		private CheckBox chkBox_SetAwake;
		private CheckBox chkBox_SetShow;
	}
}
