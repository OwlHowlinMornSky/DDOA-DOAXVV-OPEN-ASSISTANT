namespace Helper.Step {
	public enum Type {
		None = 0,

		StartUp,
		Daily,
		Room,
		Challenge,
		Spring,
		Award,
		Exit,

		COUNT,

		DebugTask = 999,
	};

	internal interface IStep {
		/// <summary>
		/// 运行该步骤。
		/// </summary>
		/// <param name="ct">任务取消之标志。</param>
		internal void Run(CancellationToken ct);

		/// <summary>
		/// 创建一个步骤实例。
		/// </summary>
		/// <param name="type">步骤类型。</param>
		/// <returns>步骤实例。若 名称无效 或 因其他问题创建失败，返回 null。</returns>
		static internal IStep CreateStep(Type type) {
			return type switch {
				Type.StartUp => new StartGame(),
				Type.Daily => new Daily(),
				Type.Room => throw new NotImplementedException("Step 'Room' not implemented."),
				Type.Challenge => new Challenge(),
				Type.Spring => throw new NotImplementedException("Step 'Spring' not implemented."),
				Type.Award => throw new NotImplementedException("Step 'Award' not implemented."),
				Type.Exit => throw new NotImplementedException("Step 'Exit' not implemented."),
				Type.DebugTask => new Debug(),
				_ => throw new NoSuchStepException()
			};
		}

		static protected void TaskSleep(TimeSpan time) {

		}
	}

}
