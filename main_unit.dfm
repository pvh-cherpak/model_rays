object Form1: TForm1
  Left = 0
  Top = 0
  Caption = #1052#1086#1076#1077#1083#1080#1088#1086#1074#1072#1085#1080#1077' '#1086#1087#1090#1080#1095#1077#1089#1082#1080#1093' '#1083#1091#1095#1077#1081
  ClientHeight = 1030
  ClientWidth = 1906
  Color = clBtnFace
  DoubleBuffered = True
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -21
  Font.Name = 'Segoe UI'
  Font.Style = []
  Menu = MainMenu1
  Position = poDesigned
  PrintScale = poNone
  Scaled = False
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  OnResize = FormResize
  DesignSize = (
    1906
    1030)
  TextHeight = 30
  object Image1: TImage
    Left = 0
    Top = 0
    Width = 1647
    Height = 945
    Align = alClient
    AutoSize = True
    OnClick = Image1Click
    OnMouseDown = Image1MouseDown
    OnMouseMove = Image1MouseMove
    ExplicitWidth = 881
    ExplicitHeight = 545
  end
  object Label1: TLabel
    Left = 1960
    Top = 150
    Width = 60
    Height = 30
    Margins.Left = 4
    Margins.Top = 4
    Margins.Right = 4
    Margins.Bottom = 4
    Caption = 'Label1'
  end
  object Memo1: TMemo
    Left = 1163
    Top = 824
    Width = 265
    Height = 121
    Anchors = [akRight, akBottom]
    Font.Charset = DEFAULT_CHARSET
    Font.Color = clWindowText
    Font.Height = -16
    Font.Name = 'Segoe UI'
    Font.Style = []
    ParentFont = False
    TabOrder = 0
    Visible = False
  end
  object GridPanel1: TGridPanel
    Left = 1647
    Top = 0
    Width = 259
    Height = 945
    Margins.Left = 4
    Margins.Top = 4
    Margins.Right = 4
    Margins.Bottom = 4
    Align = alRight
    ColumnCollection = <
      item
        Value = 100.000000000000000000
      end>
    ControlCollection = <
      item
        Column = 0
        Control = Button1
        Row = 0
      end
      item
        Column = 0
        Control = ComboBox1
        Row = 1
      end
      item
        Column = 0
        Control = LabeledEdit1
        Row = 2
      end
      item
        Column = 0
        Control = LabeledEdit2
        Row = 3
      end
      item
        Column = 0
        Control = LabeledEdit3
        Row = 4
      end
      item
        Column = 0
        Control = LabeledEdit4
        Row = 5
      end
      item
        Column = 0
        Control = LabeledEdit5
        Row = 6
      end
      item
        Column = 0
        Control = LabeledEditN
        Row = 7
      end
      item
        Column = 0
        Control = LabeledEditX
        Row = 8
      end
      item
        Column = 0
        Control = LabeledEditY
        Row = 9
      end
      item
        Column = 0
        Control = ButtonReject
        Row = 11
      end
      item
        Column = 0
        Control = ButtonAccept
        Row = 10
      end>
    RowCollection = <
      item
        SizeStyle = ssAuto
      end
      item
        SizeStyle = ssAuto
      end
      item
        SizeStyle = ssAuto
      end
      item
        SizeStyle = ssAuto
      end
      item
        SizeStyle = ssAuto
      end
      item
        SizeStyle = ssAuto
      end
      item
        SizeStyle = ssAuto
      end
      item
        SizeStyle = ssAuto
      end
      item
        SizeStyle = ssAuto
      end
      item
        SizeStyle = ssAuto
      end
      item
        SizeStyle = ssAuto
      end
      item
        SizeStyle = ssAuto
      end
      item
        SizeStyle = ssAuto
      end
      item
        SizeStyle = ssAuto
      end>
    ShowCaption = False
    TabOrder = 1
    ExplicitLeft = 1645
    ExplicitHeight = 937
    object Button1: TButton
      Left = 1
      Top = 1
      Width = 257
      Height = 61
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Align = alClient
      Caption = #1056#1072#1089#1089#1095#1080#1090#1072#1090#1100' '#1089#1094#1077#1085#1091
      TabOrder = 0
      OnClick = Button1Click
    end
    object ComboBox1: TComboBox
      Left = 1
      Top = 62
      Width = 257
      Height = 38
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Align = alClient
      TabOrder = 1
      Text = #1042#1099#1073#1077#1088#1080#1090#1077
      OnChange = ComboBox1Change
      Items.Strings = (
        #1055#1086#1083#1077
        #1051#1091#1095
        'N-'#1091#1075#1086#1083#1100#1085#1080#1082
        #1057#1074#1077#1076#1077#1085#1080#1103)
    end
    object LabeledEdit1: TLabeledEdit
      Left = 1
      Top = 133
      Width = 256
      Height = 38
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      EditLabel.Width = 118
      EditLabel.Height = 30
      EditLabel.Margins.Left = 4
      EditLabel.Margins.Top = 4
      EditLabel.Margins.Right = 4
      EditLabel.Margins.Bottom = 4
      EditLabel.Caption = 'LabeledEdit1'
      TabOrder = 2
      Text = ''
      Visible = False
    end
    object LabeledEdit2: TLabeledEdit
      Left = 1
      Top = 204
      Width = 256
      Height = 38
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      EditLabel.Width = 118
      EditLabel.Height = 30
      EditLabel.Margins.Left = 4
      EditLabel.Margins.Top = 4
      EditLabel.Margins.Right = 4
      EditLabel.Margins.Bottom = 4
      EditLabel.Caption = 'LabeledEdit2'
      TabOrder = 3
      Text = ''
      Visible = False
    end
    object LabeledEdit3: TLabeledEdit
      Left = 1
      Top = 275
      Width = 256
      Height = 38
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      EditLabel.Width = 118
      EditLabel.Height = 30
      EditLabel.Margins.Left = 4
      EditLabel.Margins.Top = 4
      EditLabel.Margins.Right = 4
      EditLabel.Margins.Bottom = 4
      EditLabel.Caption = 'LabeledEdit3'
      TabOrder = 4
      Text = ''
      Visible = False
    end
    object LabeledEdit4: TLabeledEdit
      Left = 1
      Top = 346
      Width = 256
      Height = 38
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      EditLabel.Width = 118
      EditLabel.Height = 30
      EditLabel.Margins.Left = 4
      EditLabel.Margins.Top = 4
      EditLabel.Margins.Right = 4
      EditLabel.Margins.Bottom = 4
      EditLabel.Caption = 'LabeledEdit4'
      TabOrder = 5
      Text = ''
      Visible = False
    end
    object LabeledEdit5: TLabeledEdit
      Left = 1
      Top = 417
      Width = 256
      Height = 38
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      EditLabel.Width = 118
      EditLabel.Height = 30
      EditLabel.Margins.Left = 5
      EditLabel.Margins.Top = 5
      EditLabel.Margins.Right = 5
      EditLabel.Margins.Bottom = 5
      EditLabel.Caption = 'LabeledEdit5'
      TabOrder = 6
      Text = ''
      Visible = False
    end
    object LabeledEditN: TLabeledEdit
      Left = 1
      Top = 488
      Width = 256
      Height = 38
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      EditLabel.Width = 16
      EditLabel.Height = 30
      EditLabel.Margins.Left = 4
      EditLabel.Margins.Top = 4
      EditLabel.Margins.Right = 4
      EditLabel.Margins.Bottom = 4
      EditLabel.Caption = 'N'
      TabOrder = 7
      Text = ''
      Visible = False
    end
    object LabeledEditX: TLabeledEdit
      Left = 1
      Top = 559
      Width = 256
      Height = 38
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      EditLabel.Width = 12
      EditLabel.Height = 30
      EditLabel.Margins.Left = 4
      EditLabel.Margins.Top = 4
      EditLabel.Margins.Right = 4
      EditLabel.Margins.Bottom = 4
      EditLabel.Caption = 'X'
      TabOrder = 8
      Text = ''
      Visible = False
    end
    object LabeledEditY: TLabeledEdit
      Left = 1
      Top = 630
      Width = 256
      Height = 38
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      EditLabel.Width = 12
      EditLabel.Height = 30
      EditLabel.Margins.Left = 4
      EditLabel.Margins.Top = 4
      EditLabel.Margins.Right = 4
      EditLabel.Margins.Bottom = 4
      EditLabel.Caption = 'Y'
      TabOrder = 9
      Text = ''
      Visible = False
    end
    object ButtonReject: TButton
      Left = 1
      Top = 713
      Width = 257
      Height = 32
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Align = alClient
      Caption = #1054#1090#1082#1083#1086#1085#1080#1090#1100
      TabOrder = 11
      Visible = False
      OnClick = ButtonRejectClick
    end
    object ButtonAccept: TButton
      Left = 1
      Top = 668
      Width = 257
      Height = 45
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Align = alClient
      Caption = #1055#1088#1080#1085#1103#1090#1100
      TabOrder = 10
      Visible = False
      OnClick = ButtonAcceptClick
    end
  end
  object Panel1: TPanel
    Left = 0
    Top = 945
    Width = 1906
    Height = 85
    Margins.Left = 4
    Margins.Top = 4
    Margins.Right = 4
    Margins.Bottom = 4
    Align = alBottom
    Caption = 'Panel1'
    ShowCaption = False
    TabOrder = 2
    ExplicitTop = 937
    ExplicitWidth = 1904
    object LabelDrawScene: TLabel
      Left = 14
      Top = 8
      Width = 152
      Height = 30
      Margins.Left = 5
      Margins.Top = 5
      Margins.Right = 5
      Margins.Bottom = 5
      Caption = 'LabelDrawScene'
    end
    object LabelTimeHeatMap: TLabel
      Left = 624
      Top = 7
      Width = 313
      Height = 30
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Caption = #1042#1088#1077#1084#1103' '#1088#1072#1089#1095#1105#1090#1072' '#1090#1077#1087#1083#1086#1074#1086#1081' '#1082#1072#1088#1090#1099': '
    end
    object LabelTimeScene: TLabel
      Left = 14
      Top = 56
      Width = 149
      Height = 30
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Caption = 'LabelTimeScene'
    end
    object LabelVersion: TLabel
      Left = 624
      Top = 51
      Width = 117
      Height = 30
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Caption = 'LabelVersion'
    end
  end
  object Panel2: TPanel
    Left = 1428
    Top = 844
    Width = 219
    Height = 101
    Margins.Left = 4
    Margins.Top = 4
    Margins.Right = 4
    Margins.Bottom = 4
    Anchors = [akRight, akBottom]
    ShowCaption = False
    TabOrder = 3
    DesignSize = (
      219
      101)
    object LabelN: TLabel
      Left = 5
      Top = 56
      Width = 65
      Height = 30
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Anchors = []
      Caption = 'LabelN'
    end
    object LabelPosition: TLabel
      Left = 5
      Top = 2
      Width = 122
      Height = 30
      Margins.Left = 4
      Margins.Top = 4
      Margins.Right = 4
      Margins.Bottom = 4
      Anchors = []
      Caption = 'LabelPosition'
    end
  end
  object MainMenu1: TMainMenu
    Left = 40
    Top = 8
    object N1: TMenuItem
      Caption = #1060#1072#1081#1083
      object N2: TMenuItem
        Caption = #1054#1095#1080#1089#1090#1080#1090#1100' '#1089#1094#1077#1085#1091
        OnClick = N2Click
      end
      object N3: TMenuItem
        Caption = #1057#1086#1093#1085#1072#1080#1090#1100' '#1089#1094#1077#1085#1091
        OnClick = N3Click
      end
      object N4: TMenuItem
        Caption = #1057#1086#1093#1088#1072#1085#1080#1090#1100' '#1090#1088#1072#1077#1082#1090#1086#1088#1080#1102
        OnClick = N4Click
      end
      object N5: TMenuItem
        Caption = #1047#1072#1075#1088#1091#1079#1080#1090#1100' '#1089#1094#1077#1085#1091
        OnClick = N5Click
      end
    end
    object N6: TMenuItem
      Caption = #1054#1090#1086#1073#1088#1072#1078#1077#1085#1080#1077
      object N7: TMenuItem
        Caption = #1062#1074#1077#1090' '#1084#1080#1085#1080#1084#1091#1084#1072' '#1090#1077#1087#1083#1086#1074#1086#1081' '#1082#1072#1088#1090#1099
        OnClick = N7Click
      end
      object N8: TMenuItem
        Caption = #1062#1074#1077#1090' '#1084#1072#1082#1089#1080#1084#1091#1084#1072' '#1090#1077#1087#1083#1086#1074#1086#1081' '#1082#1072#1088#1090#1099
        OnClick = N8Click
      end
      object N9: TMenuItem
        Caption = #1062#1074#1077#1090' '#1083#1091#1095#1072
        OnClick = N9Click
      end
      object N10: TMenuItem
        Caption = #1062#1074#1077#1090' '#1085#1077#1082#1086#1088#1077#1082#1090#1085#1086#1075#1086' '#1083#1091#1095#1072
        OnClick = N10Click
      end
    end
    object N11: TMenuItem
      Caption = #1058#1077#1089#1090#1099
      object N12: TMenuItem
        Caption = #1042#1088#1077#1084#1103' '#1086#1090#1088#1080#1089#1086#1074#1082#1080' '#1083#1091#1095#1072
        object N13: TMenuItem
          Caption = #1053#1072#1089#1090#1088#1086#1081#1082#1072
          OnClick = N13Click
        end
        object N14: TMenuItem
          Caption = #1047#1072#1087#1091#1089#1082
          OnClick = N14Click
        end
      end
    end
  end
  object OpenTextFileDialog1: TOpenTextFileDialog
    DefaultExt = 'txt'
    Left = 40
    Top = 120
  end
  object SaveTextFileDialog1: TSaveTextFileDialog
    DefaultExt = 'txt'
    Left = 40
    Top = 64
  end
  object ColorDialog1: TColorDialog
    Left = 40
    Top = 176
  end
  object Timer1: TTimer
    Enabled = False
    Interval = 500
    OnTimer = Timer1Timer
    Left = 144
    Top = 8
  end
end
