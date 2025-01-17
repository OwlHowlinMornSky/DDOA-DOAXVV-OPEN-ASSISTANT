using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Helper {
	public static class Global {
		public static Worker Worker { get; } = new();
		public static PatternManager PatternManager { get; } = new();
		internal static WndHandler WndHandler { get; } = new();
	}
}
