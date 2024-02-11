/**
 * LoadingScreen.c
 *
 * DayZ Custom Loading Screen
 * 2024 TheGamingChief
 * Newest version inspirited by salutesh’s community loading screen mod.
 * Simplified for a single loading screen image and compatibility for DayZ with or without the DayZ Expansion mod.
 *
 * This work is licensed under the GNU General Public License v3.0
 * To view a copy of this license, visit https://www.gnu.org/licenses/gpl-3.0.en.html.
 *
*/

class SimpleLoadingScreenData
{
    string ImagePath = "Loadingscreen/loadingscreen.edds";  // Hard-coded path to your loading screen image
};

modded class LoginScreenBase
{
    protected ImageWidget m_SimpleBackground;

    protected ref SimpleLoadingScreenData m_SimpleLoadingScreenData;

    void LoginScreenBase()
    {
        m_SimpleLoadingScreenData = new SimpleLoadingScreenData();
        if (!m_SimpleLoadingScreenData)
            return;
    }

    override Widget Init()
    {
        Widget layoutRoot = super.Init();

        m_SimpleBackground = ImageWidget.Cast(layoutRoot.FindAnyWidget("Background"));

        SetSimpleBackgroundImage();

        return layoutRoot;
    }

    protected void SetSimpleBackgroundImage()
    {
        if (m_SimpleLoadingScreenData && m_SimpleLoadingScreenData.ImagePath != string.Empty)
        {
            Print(ToString() + "::SetSimpleBackgroundImage - Background: " + m_SimpleLoadingScreenData.ImagePath);
            m_SimpleBackground.LoadImageFile(0, m_SimpleLoadingScreenData.ImagePath, true);
            m_SimpleBackground.SetImage(0);
        }
    }
};

modded class LoginQueueBase
{
    override Widget Init()
    {
        Widget layoutRoot = super.Init();

        m_SimpleBackground = ImageWidget.Cast(layoutRoot.FindAnyWidget("Background"));

        SetSimpleBackgroundImage();

        return layoutRoot;
    }
};

modded class LoginTimeBase
{
    override Widget Init()
    {
        Widget layoutRoot = super.Init();

        m_SimpleBackground = ImageWidget.Cast(layoutRoot.FindAnyWidget("Background"));

        SetSimpleBackgroundImage();

        return layoutRoot;
    }
};

modded class LoadingScreen
{
    protected Widget m_SimplePanelWidget;

    protected ref SimpleLoadingScreenData m_SimpleLoadingScreenData;

    void LoadingScreen(DayZGame game)
    {
        m_SimpleLoadingScreenData = new SimpleLoadingScreenData();
        if (!m_SimpleLoadingScreenData)
            return;

        m_SimplePanelWidget = Widget.Cast(m_WidgetRoot.FindAnyWidget("PanelWidget1"));

        // Remove vanilla mask texture
        m_ImageWidgetBackground.LoadMaskTexture("");

        if (m_SimpleLoadingScreenData.ImagePath != string.Empty)
        {
            Print(ToString() + "::Loadingscreen - Setting up simple background: " + m_SimpleLoadingScreenData.ImagePath);
            m_ImageWidgetBackground.LoadImageFile(0, m_SimpleLoadingScreenData.ImagePath, true);
            m_ImageWidgetBackground.SetImage(0);
        }
    }
};
