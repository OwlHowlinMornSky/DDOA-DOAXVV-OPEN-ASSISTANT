namespace WinFormsGUI {
	partial class UserControlSetForLegacyCha {
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
			gpBox_AwardSet = new GroupBox();
			radioBtn_AwardIgnore = new RadioButton();
			radioBtn_AwardPlay = new RadioButton();
			radioBtn_AwardNo = new RadioButton();
			gpBox_GameSet = new GroupBox();
			radioBtn_GameNew = new RadioButton();
			radioBtn_GameLast = new RadioButton();
			gpBox_AwardSet.SuspendLayout();
			gpBox_GameSet.SuspendLayout();
			SuspendLayout();
			// 
			// gpBox_AwardSet
			// 
			gpBox_AwardSet.Controls.Add(radioBtn_AwardIgnore);
			gpBox_AwardSet.Controls.Add(radioBtn_AwardPlay);
			gpBox_AwardSet.Controls.Add(radioBtn_AwardNo);
			gpBox_AwardSet.Location = new Point(3, 89);
			gpBox_AwardSet.Name = "gpBox_AwardSet";
			gpBox_AwardSet.Size = new Size(200, 107);
			gpBox_AwardSet.TabIndex = 5;
			gpBox_AwardSet.TabStop = false;
			gpBox_AwardSet.Text = "奖励挑战赛";
			// 
			// radioBtn_AwardIgnore
			// 
			radioBtn_AwardIgnore.AutoSize = true;
			radioBtn_AwardIgnore.ImeMode = ImeMode.NoControl;
			radioBtn_AwardIgnore.Location = new Point(6, 76);
			radioBtn_AwardIgnore.Name = "radioBtn_AwardIgnore";
			radioBtn_AwardIgnore.Size = new Size(86, 21);
			radioBtn_AwardIgnore.TabIndex = 2;
			radioBtn_AwardIgnore.Text = "忽略并继续";
			radioBtn_AwardIgnore.UseVisualStyleBackColor = true;
			// 
			// radioBtn_AwardPlay
			// 
			radioBtn_AwardPlay.AutoSize = true;
			radioBtn_AwardPlay.ImeMode = ImeMode.NoControl;
			radioBtn_AwardPlay.Location = new Point(6, 49);
			radioBtn_AwardPlay.Name = "radioBtn_AwardPlay";
			radioBtn_AwardPlay.Size = new Size(74, 21);
			radioBtn_AwardPlay.TabIndex = 1;
			radioBtn_AwardPlay.Text = "尝试进入";
			radioBtn_AwardPlay.UseVisualStyleBackColor = true;
			// 
			// radioBtn_AwardNo
			// 
			radioBtn_AwardNo.AutoSize = true;
			radioBtn_AwardNo.Checked = true;
			radioBtn_AwardNo.ImeMode = ImeMode.NoControl;
			radioBtn_AwardNo.Location = new Point(6, 22);
			radioBtn_AwardNo.Name = "radioBtn_AwardNo";
			radioBtn_AwardNo.Size = new Size(62, 21);
			radioBtn_AwardNo.TabIndex = 0;
			radioBtn_AwardNo.TabStop = true;
			radioBtn_AwardNo.Text = "不检测";
			radioBtn_AwardNo.UseVisualStyleBackColor = true;
			// 
			// gpBox_GameSet
			// 
			gpBox_GameSet.Controls.Add(radioBtn_GameNew);
			gpBox_GameSet.Controls.Add(radioBtn_GameLast);
			gpBox_GameSet.Location = new Point(3, 3);
			gpBox_GameSet.Name = "gpBox_GameSet";
			gpBox_GameSet.Size = new Size(200, 80);
			gpBox_GameSet.TabIndex = 4;
			gpBox_GameSet.TabStop = false;
			gpBox_GameSet.Text = "游戏选项";
			// 
			// radioBtn_GameNew
			// 
			radioBtn_GameNew.AutoSize = true;
			radioBtn_GameNew.ImeMode = ImeMode.NoControl;
			radioBtn_GameNew.Location = new Point(6, 49);
			radioBtn_GameNew.Name = "radioBtn_GameNew";
			radioBtn_GameNew.Size = new Size(62, 21);
			radioBtn_GameNew.TabIndex = 1;
			radioBtn_GameNew.Text = "新比赛";
			radioBtn_GameNew.UseVisualStyleBackColor = true;
			// 
			// radioBtn_GameLast
			// 
			radioBtn_GameLast.AutoSize = true;
			radioBtn_GameLast.Checked = true;
			radioBtn_GameLast.ImeMode = ImeMode.NoControl;
			radioBtn_GameLast.Location = new Point(6, 22);
			radioBtn_GameLast.Name = "radioBtn_GameLast";
			radioBtn_GameLast.Size = new Size(86, 21);
			radioBtn_GameLast.TabIndex = 0;
			radioBtn_GameLast.TabStop = true;
			radioBtn_GameLast.Text = "上一次比赛";
			radioBtn_GameLast.UseVisualStyleBackColor = true;
			// 
			// UserControlSetForLegacyCha
			// 
			AutoScaleDimensions = new SizeF(7F, 17F);
			AutoScaleMode = AutoScaleMode.Font;
			Controls.Add(gpBox_AwardSet);
			Controls.Add(gpBox_GameSet);
			Name = "UserControlSetForLegacyCha";
			Size = new Size(210, 294);
			gpBox_AwardSet.ResumeLayout(false);
			gpBox_AwardSet.PerformLayout();
			gpBox_GameSet.ResumeLayout(false);
			gpBox_GameSet.PerformLayout();
			ResumeLayout(false);
		}

		#endregion

		private GroupBox gpBox_AwardSet;
		private RadioButton radioBtn_AwardIgnore;
		private RadioButton radioBtn_AwardPlay;
		private RadioButton radioBtn_AwardNo;
		private GroupBox gpBox_GameSet;
		private RadioButton radioBtn_GameNew;
		private RadioButton radioBtn_GameLast;
	}
}
