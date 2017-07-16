#include "Editor.h"

Editor::Editor()
{
}

Editor::~Editor()
{
	ImGui_ImplSdlGL3_Shutdown();
}

void Editor::editorLog(std::string msg)
{
	console.AddLog(msg.c_str());
}

void Editor::create()
{
	ImGui_ImplSdlGL3_Init(m_editor.getWindow());
	console.AddLog("Editor Started\n");
}
void Editor::resize(unsigned width, unsigned height)
{
	console.AddLog("Editor size %d x %d\n", width, height);
	ImGui::GetIO().DisplaySize.x = (float)width;
	ImGui::GetIO().DisplaySize.y = (float)height;
	glViewport(0, 0, width, height);
}

void Editor::keyboardInput(InputEvent & e)
{
}

void Editor::mouseInput(InputEvent & e)
{
}

void Editor::editorEvents(SDL_Event & e)
{
	ImGui_ImplSdlGL3_ProcessEvent(&e);
}

void Editor::update(double delta)
{

}

void Editor::projectViewport()
{
	glViewport(155, 155, (GLsizei) ImGui::GetIO().DisplaySize.x / 2, (GLsizei) ImGui::GetIO().DisplaySize.y / 2);

	glBegin(GL_TRIANGLES);                     // Drawing Using Triangles
	glVertex3f(0.0f, 1.0f, 0.0f);              // Top
	glVertex3f(-1.0f, -1.0f, 0.0f);            // Bottom Left
	glVertex3f(1.0f, -1.0f, 0.0f);             // Bottom Right
	glEnd();
}


void ShowExampleMenuFile()
{
	ImGui::MenuItem("(dummy menu)", NULL, false, false);
	if (ImGui::MenuItem("New")) {}
	if (ImGui::MenuItem("Open", "Ctrl+O")) {}
	if (ImGui::BeginMenu("Open Recent"))
	{
		ImGui::MenuItem("fish_hat.c");
		ImGui::MenuItem("fish_hat.inl");
		ImGui::MenuItem("fish_hat.h");
		if (ImGui::BeginMenu("More.."))
		{
			ImGui::MenuItem("Hello");
			ImGui::MenuItem("Sailor");
			if (ImGui::BeginMenu("Recurse.."))
			{
				ShowExampleMenuFile();
				ImGui::EndMenu();
			}
			ImGui::EndMenu();
		}
		ImGui::EndMenu();
	}
	if (ImGui::MenuItem("Save", "Ctrl+S")) {}
	if (ImGui::MenuItem("Save As..")) {}
	ImGui::Separator();
	if (ImGui::BeginMenu("Options"))
	{
		static bool enabled = true;
		ImGui::MenuItem("Enabled", "", &enabled);
		ImGui::BeginChild("child", ImVec2(0, 60), true);
		for (int i = 0; i < 10; i++)
			ImGui::Text("Scrolling Text %d", i);
		ImGui::EndChild();
		static float f = 0.5f;
		static int n = 0;
		ImGui::SliderFloat("Value", &f, 0.0f, 1.0f);
		ImGui::InputFloat("Input", &f, 0.1f);
		ImGui::Combo("Combo", &n, "Yes\0No\0Maybe\0\0");
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Colors"))
	{
		for (int i = 0; i < ImGuiCol_COUNT; i++)
			ImGui::MenuItem(ImGui::GetStyleColName((ImGuiCol)i));
		ImGui::EndMenu();
	}
	if (ImGui::BeginMenu("Disabled", false)) // Disabled
	{
		IM_ASSERT(0);
	}
	if (ImGui::MenuItem("Checked", NULL, true)) {}
	if (ImGui::MenuItem("Quit", "Alt+F4")) { }
}

void Editor::render()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	ImGui_ImplSdlGL3_NewFrame(m_editor.getWindow());

	// This creates a window
	if (ImGui::BeginMainMenuBar())
	{
		if (ImGui::BeginMenu("File"))
		{
			ShowExampleMenuFile();
			ImGui::EndMenu();
		}
		if (ImGui::BeginMenu("Edit"))
		{
			if (ImGui::MenuItem("Undo", "CTRL+Z")) {}
			if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {}  // Disabled item
			ImGui::Separator();
			if (ImGui::MenuItem("Cut", "CTRL+X")) {}
			if (ImGui::MenuItem("Copy", "CTRL+C")) {}
			if (ImGui::MenuItem("Paste", "CTRL+V")) {}
			ImGui::EndMenu();
		}
		ImGui::EndMainMenuBar();
	}

	console.Draw("Output");

	// ImGui functions end here
	glViewport(0, 0, ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y);
	ImGui::Render();
	projectViewport();

}

int main(int argc, char *args[])
{
	Editor e;
	return 0;
}