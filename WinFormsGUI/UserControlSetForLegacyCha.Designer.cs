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
			gpBox_AwardMatch = new GroupBox();
			radioBtn_AwardIgnore = new RadioButton();
			radioBtn_AwardPlay = new RadioButton();
			radioBtn_AwardNo = new RadioButton();
			gpBox_TargetMatch = new GroupBox();
			radioBtn_NewMatch = new RadioButton();
			radioBtn_PreviousMatch = new RadioButton();
			gpBox_AwardMatch.SuspendLayout();
			gpBox_TargetMatch.SuspendLayout();
			SuspendLayout();
			// 
			// gpBox_AwardMatch
			// 
			gpBox_AwardMatch.Controls.Add(radioBtn_AwardIgnore);
			gpBox_AwardMatch.Controls.Add(radioBtn_AwardPlay);
			gpBox_AwardMatch.Controls.Add(radioBtn_AwardNo);
			gpBox_AwardMatch.Location = new Point(3, 89);
			gpBox_AwardMatch.Name = "gpBox_AwardMatch";
			gpBox_AwardMatch.Size = new Size(200, 107);
			gpBox_AwardMatch.TabIndex = 5;
			gpBox_AwardMatch.TabStop = false;
			gpBox_AwardMatch.Text = "奖励挑战赛";
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
			radioBtn_AwardIgnore.CheckedChanged += AwardMatch_RadioBtn_CheckedChanged;
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
			radioBtn_AwardPlay.CheckedChanged += AwardMatch_RadioBtn_CheckedChanged;
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
			radioBtn_AwardNo.CheckedChanged += AwardMatch_RadioBtn_CheckedChanged;
			// 
			// gpBox_TargetMatch
			// 
			gpBox_TargetMatch.Controls.Add(radioBtn_NewMatch);
			gpBox_TargetMatch.Controls.Add(radioBtn_PreviousMatch);
			gpBox_TargetMatch.Location = new Point(3, 3);
			gpBox_TargetMatch.Name = "gpBox_TargetMatch";
			gpBox_TargetMatch.Size = new Size(200, 80);
			gpBox_TargetMatch.TabIndex = 4;
			gpBox_TargetMatch.TabStop = false;
			gpBox_TargetMatch.Text = "游戏选项";
			// 
			// radioBtn_NewMatch
			// 
			radioBtn_NewMatch.AutoSize = true;
			radioBtn_NewMatch.ImeMode = ImeMode.NoControl;
			radioBtn_NewMatch.Location = new Point(6, 49);
			radioBtn_NewMatch.Name = "radioBtn_NewMatch";
			radioBtn_NewMatch.Size = new Size(62, 21);
			radioBtn_NewMatch.TabIndex = 1;
			radioBtn_NewMatch.Text = "新比赛";
			radioBtn_NewMatch.UseVisualStyleBackColor = true;
			radioBtn_NewMatch.CheckedChanged += MatchSet_RadioBtn_CheckedChanged;
			// 
			// radioBtn_PreviousMatch
			// 
			radioBtn_PreviousMatch.AutoSize = true;
			radioBtn_PreviousMatch.Checked = true;
			radioBtn_PreviousMatch.ImeMode = ImeMode.NoControl;
			radioBtn_PreviousMatch.Location = new Point(6, 22);
			radioBtn_PreviousMatch.Name = "radioBtn_PreviousMatch";
			radioBtn_PreviousMatch.Size = new Size(86, 21);
			radioBtn_PreviousMatch.TabIndex = 0;
			radioBtn_PreviousMatch.TabStop = true;
			radioBtn_PreviousMatch.Text = "上一次比赛";
			radioBtn_PreviousMatch.UseVisualStyleBackColor = true;
			radioBtn_PreviousMatch.CheckedChanged += MatchSet_RadioBtn_CheckedChanged;
			// 
			// UserControlSetForLegacyCha
			// 
			AutoScaleDimensions = new SizeF(7F, 17F);
			AutoScaleMode = AutoScaleMode.Font;
			Controls.Add(gpBox_AwardMatch);
			Controls.Add(gpBox_TargetMatch);
			Name = "UserControlSetForLegacyCha";
			Size = new Size(210, 294);
			gpBox_AwardMatch.ResumeLayout(false);
			gpBox_AwardMatch.PerformLayout();
			gpBox_TargetMatch.ResumeLayout(false);
			gpBox_TargetMatch.PerformLayout();
			ResumeLayout(false);
		}

		#endregion

		private GroupBox gpBox_AwardMatch;
		private RadioButton radioBtn_AwardIgnore;
		private RadioButton radioBtn_AwardPlay;
		private RadioButton radioBtn_AwardNo;
		private GroupBox gpBox_TargetMatch;
		private RadioButton radioBtn_NewMatch;
		private RadioButton radioBtn_PreviousMatch;
	}
}
