#pragma once

#ifdef PHOENIX_PLATFORM_WINDOWS

extern Phoenix::Application* Phoenix::CreateApplication();

int main(int argc, char** argv)
{
	Phoenix::Log::Init();
	PN_CORE_WARN("Initialized Log!");
	int a = 5;
	PN_INFO("Hello! Var={0}", a);

	auto app = Phoenix::CreateApplication();
	app->Run();
	delete app;
}

#endif