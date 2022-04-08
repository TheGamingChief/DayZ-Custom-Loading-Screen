modded class LoginQueueBase extends UIScriptedMenu
{
	protected TextWidget m_txtPosition;
	protected TextWidget m_txtNote;
	protected ButtonWidget m_btnLeave;
	
	protected int m_iPosition; // position in login queue
	protected bool m_IsStatic;
	
	void LoginQueueBase()
	{
		m_iPosition = -1;
		m_IsStatic = false;
		g_Game.SetKeyboardHandle(this);	
	}

	void ~LoginQueueBase()
	{
		g_Game.SetKeyboardHandle(NULL);	
	}
	
	override Widget Init()
	{	
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("Loadingscreen/gui/ftm_dialog_queue_position.layout");
		
		m_txtPosition = TextWidget.Cast( layoutRoot.FindAnyWidget("txtPosition") );
		m_txtNote = TextWidget.Cast( layoutRoot.FindAnyWidget("txtNote") );
		m_btnLeave = ButtonWidget.Cast( layoutRoot.FindAnyWidget("btnLeave") );
		#ifdef PLATFORM_CONSOLE
		m_btnLeave.Show(false);
		layoutRoot.FindAnyWidget("toolbar_bg").Show(true);
		#ifdef PLATFORM_PS4
			string back = "circle";
			if( GetGame().GetInput().GetEnterButton() == GamepadButton.A )
			{
				back = "circle";
			}
			else
			{
				back = "cross";
			}
			ImageWidget toolbar_b = layoutRoot.FindAnyWidget( "BackIcon" );
			toolbar_b.LoadImageFile( 0, "set:playstation_buttons image:" + back );
		#endif
		#endif
		return layoutRoot;
	}
	
	override void Update(float timeslice)
	{
		if ( GetGame().GetInput().LocalPress("UAUIBack", false) )
		{
			Leave();
		}
	}
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		super.OnClick(w, x, y, button);
		if ( w == m_btnLeave )
		{
			Leave();
			return true;
		}
		return false;
	}
	
	void Show()
	{
		if (layoutRoot)
			layoutRoot.Show(true);
	}
	
	void Hide()
	{
		if (layoutRoot)
			layoutRoot.Show(false);
	}
	
	void SetPosition(int position)
	{
		if ( position != m_iPosition )
		{
			m_iPosition = position;
			m_txtPosition.SetText(position.ToString());
		}
	}
	
	bool IsStatic()
	{
		return m_IsStatic;
	}
	
	void Leave()
	{
	#ifdef PLATFORM_CONSOLE
		g_Game.SetGameState( DayZGameState.MAIN_MENU );
		g_Game.SetLoadState( DayZLoadState.MAIN_MENU_START );
	#endif
		g_Game.GetCallQueue(CALL_CATEGORY_SYSTEM).Call(GetGame().DisconnectSessionForce);
		
		Close();
	}
};

modded class LoginTimeBase extends UIScriptedMenu
{
	protected TextWidget m_txtDescription;
	protected TextWidget m_txtLabel;
	protected ButtonWidget m_btnLeave;
	protected bool m_IsStatic;
	
	void LoginTimeBase()
	{
		g_Game.SetKeyboardHandle(this);
		m_IsStatic = false;	
	}

	void ~LoginTimeBase()
	{
		g_Game.SetKeyboardHandle(NULL);	
	}
	
	override Widget Init()
	{	
		layoutRoot = GetGame().GetWorkspace().CreateWidgets("Loadingscreen/gui/ftm_dialog_login_time.layout");
		
		m_txtDescription = TextWidget.Cast( layoutRoot.FindAnyWidget("txtDescription") );
		m_txtLabel = TextWidget.Cast( layoutRoot.FindAnyWidget("txtLabel") );
		m_btnLeave = ButtonWidget.Cast( layoutRoot.FindAnyWidget("btnLeave") );

		return layoutRoot;
	}
	
	override void Update(float timeslice)
	{
		if ( GetGame().GetInput().LocalPress("UAUIBack", false) )
		{
			Leave();
		}
	}
	
	override bool OnClick(Widget w, int x, int y, int button)
	{
		super.OnClick(w, x, y, button);
		if ( w == m_btnLeave )
		{
			Leave();
			return true;
		}
		return false;
	}
	
	void Show()
	{
		if (layoutRoot)
			layoutRoot.Show(true);
	}
	
	void Hide()
	{
		if (layoutRoot)
			layoutRoot.Show(false);
	}
	
	void SetTime(int time)
	{
		m_txtLabel.SetText("#menu_loading_in " + time.ToString() + " #dayz_game_seconds");
	}
		
	/*void SetStatus(string status)
	{
		m_txtDescription.SetText(status);
	}
	
	bool IsStatic()
	{
		return m_IsStatic;
	}*/
	
	void Leave()
	{
	#ifdef PLATFORM_CONSOLE
		g_Game.SetGameState( DayZGameState.MAIN_MENU );
		g_Game.SetLoadState( DayZLoadState.MAIN_MENU_START );
	#endif
		g_Game.GetCallQueue(CALL_CATEGORY_SYSTEM).Call(GetGame().DisconnectSessionForce);
		
		Close();
	}
};

modded class LoadingScreen
{
	ref Widget m_WidgetRoot;
	//Widget m_FrameWidgetSmall;
	//Widget m_FrameWidgetLarge;
	//ProgressBarWidget m_ProgressBarSmall;
	//ProgressBarWidget m_ProgressBarLarge;
	//ProgressBarWidget m_ProgressBar;
	TextWidget m_TextWidgetTitle;
	TextWidget m_TextWidgetStatus;
	ImageWidget m_ImageWidgetBackground;
	DayZGame m_DayZGame;
	float m_LastProgressUpdate;
	
	ImageWidget m_ImageLogoMid;
	ImageWidget m_ImageLogoCorner;
	ImageWidget m_ImageLoadingIcon;
	ImageWidget m_ImageBackground;
	ProgressBarWidget m_ProgressLoading;
	float m_ImageLoadingIconRotation;
	TextWidget m_ProgressText;
	
	//ref Timer m_Timer = new Timer(CALL_CATEGORY_SYSTEM);
	
	int m_Counter;
	ref Timer m_Timer;
	
	void LoadingScreen(DayZGame game)
	{
		
		m_DayZGame = game;
		
		m_WidgetRoot = game.GetLoadingWorkspace().CreateWidgets("Loadingscreen/gui/ftm_loading.layout");
		//m_FrameWidgetSmall = m_WidgetRoot.FindAnyWidget("ProgressBarFrameSmall");
		//m_FrameWidgetLarge = m_WidgetRoot.FindAnyWidget("ProgressBarFrameLarge");
		//Class.CastTo(m_ProgressBarSmall, m_WidgetRoot.FindAnyWidget("ProgressBarWidgetSmall"));
		//Class.CastTo(m_ProgressBarLarge, m_WidgetRoot.FindAnyWidget("ProgressBarWidgetLarge"));
		Class.CastTo(m_ImageLogoMid, m_WidgetRoot.FindAnyWidget("ImageLogoMid"));
		Class.CastTo(m_ImageLogoCorner, m_WidgetRoot.FindAnyWidget("ImageLogoCorner"));
		
		Class.CastTo(m_TextWidgetTitle, m_WidgetRoot.FindAnyWidget("TextWidget"));
		Class.CastTo(m_TextWidgetStatus, m_WidgetRoot.FindAnyWidget("StatusText"));
		Class.CastTo(m_ImageWidgetBackground, m_WidgetRoot.FindAnyWidget("ImageBackground"));
		Class.CastTo(m_ImageLoadingIcon, m_WidgetRoot.FindAnyWidget("ImageLoadingIcon"));
		
		m_ImageBackground = ImageWidget.Cast( m_WidgetRoot.FindAnyWidget("ImageBackground") );
		m_ProgressLoading = ProgressBarWidget.Cast( m_WidgetRoot.FindAnyWidget("LoadingBar") );
		
		string tmp;
		m_ProgressText = TextWidget.Cast(m_WidgetRoot.FindAnyWidget("ProgressText"));
		if (GetGame())
		{
			m_ProgressText.Show( GetGame().CommandlineGetParam("loadingTest", tmp) );
		}
		
		
			
		m_ImageLogoMid.Show(true);
		m_ImageLogoCorner.Show(false);
		
		//m_ImageLoadingIcon.Show(true);
		//m_ProgressText.Show(true);
		
		//m_ProgressBar = m_ProgressBarLarge;
		//m_ProgressBar.SetCurrent(0);
		//m_FrameWidgetSmall.Show( false );
		//m_ImageWidgetBackground.LoadImageFile( 0, GetRandomLoadingBackground() );
		m_ImageWidgetBackground.Show( true );		
		m_Counter = 0;
				
		// lighten up your desktop
		game.GetBacklit().LoadingAnim();
		
		ProgressAsync.SetProgressData(m_ProgressLoading);
		ProgressAsync.SetUserData(m_ImageBackground);
	}
	
	void OnTimer()
	{
		if ( GetGame() )
		{
			Print("Loading Update: "+ GetGame().GetTickTime());	
		}
		else
		{
			Print("Loading Update...");	
		}
	}
	
	void Inc()
	{
		m_LastProgressUpdate = m_DayZGame.GetTickTime();
		
		m_Counter++;
	Print("Loading Inc: "+ m_Counter);
		if ( m_Counter == 1 )
		{
			Show();
		}
	}
	
	void Dec()
	{
		m_Counter = m_Counter - 1;
	
		if ( m_Counter <= 0 )
		{
			m_Counter = 0;
			
			if ( m_Timer )
			{
				delete m_Timer;
			}
			
			/*
			m_Timer = new Timer();
			m_Timer.Run(2, this,"EndLoading", NULL, false);
			*/
			EndLoading();
		}
	}
	
	void EndLoading()
	{
		ProgressAsync.SetProgressData(null);
		ProgressAsync.SetUserData(null);
		m_WidgetRoot.Show( false );
		GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Call( g_Game.CheckDialogs );
	}
	
	bool IsLoading()
	{
		if ( m_WidgetRoot.IsVisible() )
		{
			return true;
		}
	
		return false;
	}
	
	void SetTitle( string title )
	{
		m_TextWidgetTitle.SetText( title );
	}
	/*
	void HideTitle()
	{
		m_TextWidgetTitle.Show(false);
	}
	
	void ShowTitle()
	{
		m_TextWidgetTitle.Show(true);
	}
	*/
	
	void SetStatus( string status )
	{
		m_TextWidgetStatus.SetText( status );
	}
	
	void SetProgress( float val )
	{
		//m_ProgressText.SetText(val.ToString() + " %");
		
		float time_delta = m_DayZGame.GetTickTime() - m_LastProgressUpdate;
		
		//m_ProgressLoading.SetCurrent( val * 100 );
		//m_ImageBackground.SetMaskProgress( val );
		
		//Print("SetProgress delta: "+ time_delta);
		
		if ( m_Counter > 0 )
		{
			//m_ImageLoadingIconRotation += 15;
			//m_ImageLoadingIcon.SetRotation(0, 0, m_ImageLoadingIconRotation);
			
			//m_ProgressBar.SetCurrent( val * 100 );
		}
		
		m_LastProgressUpdate = m_DayZGame.GetTickTime();
	}
	
	void OnUpdate( float timeslice )
	{

	}
	
	void Show()
	{
		Widget lIcon = m_ImageBackground;
		Widget pText = m_ProgressLoading;
		m_ProgressText.SetText("");
		m_ProgressLoading.SetCurrent( 0.0 );
		m_ImageBackground.SetMaskProgress( 0.0 );
		
		if ( !m_WidgetRoot.IsVisible() )
		{
			if ( m_DayZGame.GetUIManager().IsDialogVisible() )
			{
				m_DayZGame.GetUIManager().HideDialog();
			}
			
			if ( m_DayZGame.GetMissionState() == DayZGame.MISSION_STATE_MAINMENU )
			{
				//m_ProgressBar = m_ProgressBarSmall;
				m_ImageLogoMid.Show(false);
				m_ImageLogoCorner.Show(false);				
				//m_FrameWidgetSmall.Show( true );
				//m_FrameWidgetLarge.Show( false );
				m_ImageWidgetBackground.Show( true );		
				m_TextWidgetStatus.Show(true);
				//lIcon = null;
				//pText = null;
			}
			else
			{
				//m_ProgressBar = m_ProgressBarLarge;
				m_ImageLogoMid.Show(true);
				m_ImageLogoCorner.Show(false);
				//m_FrameWidgetSmall.Show( false );
				//m_FrameWidgetLarge.Show( true );
				m_ImageWidgetBackground.Show( true );
				m_TextWidgetStatus.Show(false);
			}
			
			m_WidgetRoot.Show( true );
			//m_ProgressBar.SetCurrent( 0 );
			m_TextWidgetTitle.SetText( "" );
			m_TextWidgetStatus.SetText( "" );
		}
		
		ProgressAsync.SetProgressData(pText);
		ProgressAsync.SetUserData(lIcon);
	}
	
	void Hide(bool force)
	{
		if (force)
		{
			while (m_Counter > 0)
			{
				Dec();
			}
		}

		if ( m_Counter <= 0 /*&& m_WidgetRoot.IsVisible()*/ )
		{
			m_WidgetRoot.Show( false );
			
			//Print("***** m_WidgetRoot.Show false");
			
			ProgressAsync.SetUserData(null);
			ProgressAsync.SetProgressData(null);
		}
	}
};

modded class ConnectionLost
{
	private ref Widget m_WidgetRoot;
	private TextWidget m_TextWidgetTitle;
	private float m_duration;
		
	void ConnectionLost(DayZGame game)
	{		
		m_WidgetRoot = game.GetWorkspace().CreateWidgets("Loadingscreen/gui/ftm_day_z_connection_lost.layout");
		m_WidgetRoot.Show(false);
		
		Class.CastTo(m_TextWidgetTitle, m_WidgetRoot.FindAnyWidget("TextWidget"));
		m_duration = 0.0;
	}
	
	void Show()
	{
		if ( !m_WidgetRoot.IsVisible() )
		{
			if ( g_Game.GetUIManager().IsDialogVisible() )
			{
				g_Game.GetUIManager().HideDialog();
			}
			
			m_WidgetRoot.Show( true );
			m_TextWidgetTitle.SetText( "" );
		}
	}
	
	void Hide()
	{
		if ( m_WidgetRoot.IsVisible() )
		{
			m_WidgetRoot.Show( false );
		}
	}
	
	void SetText(string text)
	{
		m_TextWidgetTitle.SetText(text);
	}
	
	float GetDuration()
	{
		return m_duration;
	}
	
	void SetDuration(float duration)
	{
		m_duration = duration;
	}
};
