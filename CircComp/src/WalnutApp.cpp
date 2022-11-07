#include "Walnut/Application.h"
#include "Walnut/EntryPoint.h"

#include "Walnut/Image.h"
#include "Walnut/Random.h"
#include "Walnut/Timer.h"

#include "Renderer.h"

class ExampleLayer : public Walnut::Layer
{
public:
	virtual void OnUIRender() override
	{
		ImGui::Begin("Hello", nullptr, ImGuiWindowFlags_NoMove);
		{
			ImGui::Text("Time taken to render: %.3fms", m_ElapsedTime);
			if (ImGui::Button("test"))
				Render();
		}
		ImGui::End();

		ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
		ImGui::Begin("View", nullptr, ImGuiWindowFlags_NoMove);
		{
			m_ViewportWidth = ImGui::GetContentRegionAvail().x;
			m_ViewportHeight = ImGui::GetContentRegionAvail().y;

			auto image = m_Renderer.GetFinalImage();
			if(image)
				ImGui::Image(image->GetDescriptorSet(), { (float)image->GetWidth(),(float)image->GetHeight() });
		}
		ImGui::End();
		ImGui::PopStyleVar();
		Render();
	}
	void Render()
	{
		Walnut::Timer timothy;

		m_Renderer.OnResize(m_ViewportWidth, m_ViewportHeight);
		m_Renderer.Render();

		m_ElapsedTime = timothy.ElapsedMillis();
	}
private:
	Renderer m_Renderer;
	uint32_t m_ViewportWidth = 0, m_ViewportHeight = 0;
	float m_ElapsedTime = 0;
};

Walnut::Application* Walnut::CreateApplication(int argc, char** argv)
{
	Walnut::ApplicationSpecification spec;
	spec.Name = "Walnut Example";

	Walnut::Application* app = new Walnut::Application(spec);
	app->PushLayer<ExampleLayer>();
	app->SetMenubarCallback([app]()
	{
		if (ImGui::BeginMenu("File"))
		{
			if (ImGui::MenuItem("Exit"))
			{
				app->Close();
			}
			ImGui::EndMenu();
		}
	});
	return app;
}