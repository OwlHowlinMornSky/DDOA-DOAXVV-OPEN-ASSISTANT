#pragma once

class AppWin32 final {
public:
	AppWin32() = default;
	~AppWin32() = default;

public:
	bool Init();

	void Run(int nShowCmd);

	void Drop();
};

extern AppWin32 app;
