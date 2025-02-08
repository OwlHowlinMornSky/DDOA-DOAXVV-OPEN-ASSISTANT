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

using static System.Windows.Forms.VisualStyles.VisualStyleElement;

namespace WinFormsGUI {
	internal class GuiLockReg {
		private Action<bool> m_register = x => { };
		internal bool Value {
			get; private set;
		}
		internal GuiLockReg(ref Action<bool> source, bool initVal = false) {
			Value = initVal;
			source = OnAction;
		}
		private void OnAction(bool val) {
			Value = val;
			m_register(val);
		}
		internal void Add(Action<bool> action) {
			m_register += action;
			if (Value)
				action(true);
		}
		internal void Rid(Action<bool> action) {
			m_register -= action;
		}
	}

	internal class TaskStatusRegistration {

		internal TaskStatusRegistration() {
			Helper.GUICallbacks.Log = (x) => { Log(x); };
			Helper.GUICallbacks.Pause = () => { Pause(); };
		}

		internal Action OnStartLock = () => { }; // 成功开始任务后，在UI线程锁定UI。

		/// <summary>
		/// 任务状态改变时锁定与解锁GUI的事件。
		/// 任务线程跑起来后，从任务线程，通知UI线程。
		/// </summary>
		internal Action<Helper.GUICallbacks.LogInfo> Log = x => { };
		internal Action Pause = () => { };
		internal GuiLockReg OnLockWork = new(ref Helper.GUICallbacks.LockTask);
		internal GuiLockReg OnLockStepDaily = new(ref Helper.GUICallbacks.LockStepDaily);
		internal GuiLockReg OnLockStepChallenge = new(ref Helper.GUICallbacks.LockStepChallenge);
	}
}
