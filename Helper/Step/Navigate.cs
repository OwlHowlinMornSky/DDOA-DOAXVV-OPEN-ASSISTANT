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

namespace Helper.Step {
	static internal class Navigate {
		public enum Page : int {
			None,

			Home, // 主页
			Challenge, // 挑战赛页面
			MatchConfirm, // 开始挑战的确认页面
			MatchResult, // 挑战结算页面
			AnyOtherHaveHomeBtn, // 任何 不确定 但 左侧有主页按钮 的页面
			AnyOtherHaveReturnBtn, // 任何 不确定 但 左侧有返回按钮 的页面

			COUNT
		};

		static private Pattern? temp_chaPage;
		static private Pattern? temp_matchPage;
		static private Pattern? temp_homePage;
		static private Pattern? temp_resultPage;
		static private Pattern? temp_anyOtherPageHaveReturn;
		static private Pattern? temp_anyOtherPageHaveHome;
		static private Pattern? temp_anyOtherPageHaveHomeW;
		static private Pattern? temp_homeChaBtn;

		static private void EnsurePatterns() {
			//CoreLog() << "Task_Navigate: Begin Load Templates." << std::endl;

			temp_chaPage ??= PatternManager.CreatePattern("default") ?? throw new Exception();
			temp_matchPage ??= PatternManager.CreatePattern("start") ?? throw new Exception();
			temp_homePage ??= PatternManager.CreatePattern("homeSpec") ?? throw new Exception();
			temp_resultPage ??= PatternManager.CreatePattern("result") ?? throw new Exception();
			temp_anyOtherPageHaveReturn ??= PatternManager.CreatePattern("back") ?? throw new Exception();
			temp_anyOtherPageHaveHome ??= PatternManager.CreatePattern("otherHome") ?? throw new Exception();
			temp_anyOtherPageHaveHomeW ??= PatternManager.CreatePattern("otherHomeAskew") ?? throw new Exception();
			temp_homeChaBtn ??= PatternManager.CreatePattern("homeChaBtn") ?? throw new Exception();

			//CoreLog() << "Task_Navigate: Finish Load Templates." << std::endl;
		}

		static public Page TryToDeterminePage() {
			EnsurePatterns();

			if (!WndHandler.SetForGame()) {
				//CoreLog() << "Task_Navigate: Window Handler Set Failed." << std::endl;
				return Page.None;
			}

			//cv::Mat mat;
			if (!WndHandler.WaitOneFrame()) {
				//CoreLog() << "Task_Navigate: Window Handler GetOneFrame Failed." << std::endl;
				return Page.None;
			}
			var mat = WndHandler.Eye;

			if (temp_homePage?.TryMatch(mat) == true) {
				//CoreLog() << "Task_Navigate: Matched: home." << std::endl;
				return Page.Home;
			}
			if (temp_chaPage?.TryMatch(mat) == true) {
				//CoreLog() << "Task_Navigate: Matched: cha." << std::endl;
				return Page.Challenge;
			}
			if (temp_matchPage?.TryMatch(mat) == true) {
				//CoreLog() << "Task_Navigate: Matched: match comfirm." << std::endl;
				return Page.MatchConfirm;
			}
			if (temp_resultPage?.TryMatch(mat) == true) {
				//CoreLog() << "Task_Navigate: Matched: match result." << std::endl;
				return Page.MatchResult;
			}
			if (temp_anyOtherPageHaveHomeW?.TryMatch(mat) == true) {
				//CoreLog() << "Task_Navigate: Matched: AnyOtherHaveHomeBtn." << std::endl;
				return Page.AnyOtherHaveHomeBtn;
			}
			if (temp_anyOtherPageHaveHome?.TryMatch(mat) == true) {
				//CoreLog() << "Task_Navigate: Matched: AnyOtherHaveHomeBtn." << std::endl;
				return Page.AnyOtherHaveHomeBtn;
			}
			if (temp_anyOtherPageHaveReturn?.TryMatch(mat) == true) {
				//CoreLog() << "Task_Navigate: Matched: AnyOtherHaveReturnBtn." << std::endl;
				return Page.AnyOtherHaveReturnBtn;
			}
			//CoreLog() << "Task_Navigate: Matche Failed." << std::endl;

			return Page.None;
		}

		static public bool NavigateTo(Page dest) {
			return NavigateFromTo(TryToDeterminePage(), dest);
		}

		static public bool NavigateFromTo(Page now, Page dest) {
			//CoreLog() << "Task_Navigate: From " << now << " to " << dest << "." << std::endl;
			////r_helper->GuiLogF_II(ReturnMsgEnum::Test_II, now, dest);
			if (now != dest) {
				switch (now) {
				case Page.Home: // 主页
					break;
				case Page.Challenge: // 挑战赛页面
				case Page.AnyOtherHaveHomeBtn: // 任何 不确定 但 左侧有主页按钮 的页面
				{
					if (temp_anyOtherPageHaveHome == null || temp_homePage == null)
						return false;
					Point pt = temp_anyOtherPageHaveHome.GetSearchRect().Location;
					pt.Offset(20, 20);
					if (!WndHandler.KeepClickingUntil(pt, temp_homePage))
						return false;
					break;
				}
				case Page.AnyOtherHaveReturnBtn: // 任何 不确定 但 左侧有返回按钮 的页面
				{
					if (temp_anyOtherPageHaveReturn == null || temp_homePage == null)
						return false;
					Point pt = temp_anyOtherPageHaveReturn.GetSearchRect().Location;
					if (!WndHandler.KeepClickingUntil(pt, temp_homePage)) {
						return false;
					}
					break;
				}
				default:
					return false;
				}
				switch (dest) {
				case Page.Challenge: {
					if (temp_homeChaBtn == null || temp_chaPage == null)
						return false;
					Point pt = temp_homeChaBtn.GetSearchRect().Location;
					pt.Offset(5, 10);
					if (!WndHandler.KeepClickingUntil(pt, temp_chaPage)) {
						return false;
					}
					break;
				}
				}
			}
			//CoreLog() << "Task_Navigate: Success." << std::endl;
			Thread.Sleep(30);
			return true;
		}

	}
}
