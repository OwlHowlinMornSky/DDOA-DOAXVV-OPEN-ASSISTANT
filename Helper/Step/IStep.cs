/*
*    DDOA-DOAXVV-OPEN-ASSISTANT
* 
*     Copyright 2023-2025  Tyler Parret True
* 
*    Licensed under the Apache License, Version 2.0 (the "License");
*    you may not use this file except in compliance with the License.
*    You may obtain a copy of the License at
* 
*        http://www.apache.org/licenses/LICENSE-2.0
* 
*    Unless required by applicable law or agreed to in writing, software
*    distributed under the License is distributed on an "AS IS" BASIS,
*    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
*    See the License for the specific language governing permissions and
*    limitations under the License.
* 
* @Authors
*    Tyler Parret True <mysteryworldgod@outlook.com><https://github.com/OwlHowlinMornSky>
*/
using System.Diagnostics;

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

	internal interface IStep : IDisposable {
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

		static internal void Log(GUICallbacks.LogInfo.Type type, string title, string? description = null) {
			GUICallbacks.Log(new(type, title, description));
		}

		static protected void TaskSleep(TimeSpan time, CancellationToken ct) {
			Stopwatch watch = new();
			while (true) {
				ct.ThrowIfCancellationRequested();
				if (time > TimeSpan.FromMilliseconds(60)) {
					Thread.Sleep(TimeSpan.FromMilliseconds(60));
					time -= watch.Elapsed;
					watch.Restart();
				}
				else if (time > TimeSpan.Zero) {
					Thread.Sleep(time);
					break;
				}
				else {
					break;
				}
			}
		}
	}

}
