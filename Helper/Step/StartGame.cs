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
using System.Drawing;
using System.Diagnostics;

namespace Helper.Step {
	internal class StartGame : IStep {
		public void Run(CancellationToken ct) {
			Stopwatch watch = new();
			Point pt;

			// LOG：任务开始【启动游戏】
			IStep.Log(
				GUICallbacks.LogInfo.Type.Info,
				LogStr.StepStartupEnter
				);

			try {
				// 检查游戏窗口是否已存在
				if (!WndHandler.GameWndAvailable()) {
					// 检查启动器窗口是否已存在
					if (!WndHandler.LaucherAvailable()) {
						// 游戏未运行（游戏窗口和启动器窗口都不存在）

						// 令steam打开doaxvv
						//system("start steam://rungameid/958260");
						HelperKernel.WndHelper.ShellStart("steam://rungameid/958260");

						// 等待启动器打开
						watch.Restart();
						while (true) {
							if (watch.Elapsed.TotalSeconds > 60)
								throw new StepErrorCriticalException("Launcher not show up.");
							if (WndHandler.LaucherAvailable())
								break;
							ct.ThrowIfCancellationRequested();
							IStep.TaskSleep(TimeSpan.FromSeconds(1), ct);
						}
					}
					// 启动器已打开，但游戏还未打开

					Pattern temp_startBtn = PatternManager.CreatePattern("StartGameBtn");
					Pattern temp_titleBtn = PatternManager.CreatePattern("startTitleTLbtn");
					Pattern temp_loading = PatternManager.CreatePattern("loading");
					Pattern temp_homeSpec = PatternManager.CreatePattern("homeSpec");

					WndHandler.SetForLauncher();

					// 寻找启动器的启动按钮
					if (!WndHandler.WaitFor(temp_startBtn, TimeSpan.FromSeconds(30)))
						throw new StepErrorCriticalException("Failed to click start button on launcher.");

					// pt 置为 点击启动器的启动按钮位置
					pt = temp_startBtn.GetSpecialPointInResultRect(0);

					// 持续点击启动，直到启动器关闭
					watch.Restart();
					while (true) {
						if (watch.Elapsed.TotalSeconds > 60)
							throw new StepErrorCriticalException("Start button on launcher clicked no respond.");
						if (!WndHandler.LaucherAvailable()) {
							break;
						}
						WndHandler.ClickAt(pt);// 点击开始。
						ct.ThrowIfCancellationRequested();
						IStep.TaskSleep(TimeSpan.FromSeconds(0.5), ct);
					}
					WndHandler.Reset();

					// 等待游戏窗口出现
					watch.Restart();
					while (true) {
						if (watch.Elapsed.TotalSeconds > 60)
							throw new StepErrorCriticalException("Game not show up.");
						if (WndHandler.GameWndAvailable()) {
							break;
						}
						ct.ThrowIfCancellationRequested();
						IStep.TaskSleep(TimeSpan.FromSeconds(1), ct);
					}

					WndHandler.SetForGame();

					// 等待游戏标题画面（左上角 选项按钮）
					if (!WndHandler.WaitFor(temp_titleBtn, TimeSpan.FromSeconds(300.0f)))
						throw new StepErrorCriticalException("Game init time too long.");

					// 持续点击直到进入主页
					pt = new(920, 40);
					if (!WndHandler.KeepClickingUntil(pt, temp_homeSpec, TimeSpan.FromSeconds(120), TimeSpan.FromSeconds(1)))
						throw new StepErrorCriticalException("Failed to enter homepage.");
				}
				else {
					// 开始时就存在游戏窗口
					WndHandler.SetForGame();

					var page = Navigate.TryToDeterminePage();

					if (!(page > 0 && page < Navigate.Page.COUNT)) { // 不确定在哪个页面

						Pattern temp_titlePage = PatternManager.CreatePattern("startTitleTLbtn");
						Pattern temp_homeSpec = PatternManager.CreatePattern("homeSpec");

						if (!WndHandler.WaitOneFrame())
							throw new StepErrorCriticalException("Failed to capture homepage.");

						if (!temp_titlePage.TryMatch(WndHandler.Eye))
							throw new StepErrorCriticalException("Unknown page.");

						// 在标题界面则尝试进入主页
						pt = new(920, 40);
						if (!WndHandler.KeepClickingUntil(pt, temp_homeSpec, TimeSpan.FromSeconds(120), TimeSpan.FromSeconds(1)))
							throw new StepErrorCriticalException("Failed to enter homepage.");
					}
				}
				IStep.Log(
					GUICallbacks.LogInfo.Type.Info,
					LogStr.StepStartupExit
					);
			}
			catch (StepErrorCriticalException ex) {
				IStep.Log(
					GUICallbacks.LogInfo.Type.Info,
					LogStr.StepStartupFailed
					);
				IStep.Log(
						GUICallbacks.LogInfo.Type.Error,
					string.Format(LogStr.StepErr_X, ex.Message)
					);
			}
			return;
		}
	}
}
