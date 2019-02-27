#pragma once
class PhysicsDebugDraw : public btIDebugDraw {
	struct SConstantBuffer {
		CMatrix mView;
		CMatrix mProj;
	};
	int m_debugMode = btIDebugDraw::DBG_NoDebug;
	int m_numLine = 0;
public:
	void drawLine(const btVector3& from, const btVector3& to, const btVector3& color) override;
	void drawContactPoint(const btVector3&, const btVector3&, btScalar, int, const btVector3&) override
	{
	}
	void reportErrorWarning(const char*) override
	{
	}
	void draw3dText(const btVector3&, const char*) override
	{
	}
	void setDebugMode(int debugMode) override
	{
		m_debugMode = debugMode;
	}
	int	getDebugMode() const override
	{
		return m_debugMode;
	}
};

