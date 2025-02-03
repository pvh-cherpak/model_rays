object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 621
  ClientWidth = 1047
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  Menu = MainMenu1
  Scaled = False
  OnCreate = FormCreate
  OnKeyDown = FormKeyDown
  TextHeight = 15
  object Image1: TImage
    Left = 8
    Top = 8
    Width = 881
    Height = 545
    OnClick = Image1Click
    OnMouseDown = Image1MouseDown
    OnMouseMove = Image1MouseMove
  end
  object LabelPosition: TLabel
    Left = 904
    Top = 530
    Width = 71
    Height = 15
    Caption = 'LabelPosition'
  end
  object LabelN: TLabel
    Left = 905
    Top = 565
    Width = 37
    Height = 15
    Caption = 'LabelN'
  end
  object LabelTimeHeatMap: TLabel
    Left = 296
    Top = 565
    Width = 178
    Height = 15
    Caption = #1042#1088#1077#1084#1103' '#1088#1072#1089#1095#1105#1090#1072' '#1090#1077#1087#1083#1086#1074#1086#1081' '#1082#1072#1088#1090#1099': '
  end
  object LabelTimeScene: TLabel
    Left = 24
    Top = 565
    Width = 85
    Height = 15
    Caption = 'LabelTimeScene'
  end
  object LabelVersion: TLabel
    Left = 585
    Top = 565
    Width = 66
    Height = 15
    Caption = 'LabelVersion'
  end
  object LabelDrawScene: TLabel
    Left = 24
    Top = 593
    Width = 3
    Height = 15
    Margins.Left = 4
    Margins.Top = 4
    Margins.Right = 4
    Margins.Bottom = 4
  end
  object Label2: TLabel
    Left = 40
    Top = 750
    Width = 43
    Height = 19
    Margins.Left = 4
    Margins.Top = 4
    Margins.Right = 4
    Margins.Bottom = 4
    Caption = 'Label2'
  end
  object Label3: TLabel
    Left = 100
    Top = 740
    Width = 43
    Height = 19
    Margins.Left = 4
    Margins.Top = 4
    Margins.Right = 4
    Margins.Bottom = 4
    Caption = 'Label3'
  end
  object Button1: TButton
    Left = 895
    Top = 8
    Width = 154
    Height = 73
    Caption = 'Button1'
    TabOrder = 0
    OnClick = Button1Click
  end
  object ComboBox1: TComboBox
    Left = 905
    Top = 101
    Width = 136
    Height = 23
    TabOrder = 1
    Text = #1051#1091#1095
    OnChange = ComboBox1Change
    Items.Strings = (
      #1055#1086#1083#1077
      #1051#1091#1095
      'N-'#1091#1075#1086#1083#1100#1085#1080#1082
      #1057#1074#1077#1076#1077#1085#1080#1103)
  end
  object LabeledEditX: TLabeledEdit
    Left = 904
    Top = 168
    Width = 121
    Height = 23
    EditLabel.Width = 7
    EditLabel.Height = 15
    EditLabel.Caption = 'X'
    TabOrder = 2
    Text = ''
    Visible = False
  end
  object LabeledEditY: TLabeledEdit
    Left = 904
    Top = 216
    Width = 121
    Height = 23
    EditLabel.Width = 7
    EditLabel.Height = 15
    EditLabel.Caption = 'Y'
    TabOrder = 3
    Text = ''
    Visible = False
  end
  object LabeledEdit3: TLabeledEdit
    Left = 905
    Top = 403
    Width = 121
    Height = 23
    EditLabel.Width = 67
    EditLabel.Height = 15
    EditLabel.Caption = 'LabeledEdit3'
    TabOrder = 4
    Text = ''
    Visible = False
  end
  object LabeledEdit4: TLabeledEdit
    Left = 905
    Top = 448
    Width = 121
    Height = 23
    EditLabel.Width = 67
    EditLabel.Height = 15
    EditLabel.Caption = 'LabeledEdit4'
    TabOrder = 5
    Text = ''
    Visible = False
  end
  object ButtonAccept: TButton
    Left = 904
    Top = 485
    Width = 57
    Height = 25
    Caption = #1055#1088#1080#1085#1103#1090#1100
    TabOrder = 6
    Visible = False
    OnClick = ButtonAcceptClick
  end
  object ButtonReject: TButton
    Left = 967
    Top = 485
    Width = 73
    Height = 25
    Caption = #1054#1090#1082#1083#1086#1085#1080#1090#1100
    TabOrder = 7
    Visible = False
    OnClick = ButtonRejectClick
  end
  object LabeledEdit1: TLabeledEdit
    Left = 905
    Top = 317
    Width = 121
    Height = 23
    EditLabel.Width = 67
    EditLabel.Height = 15
    EditLabel.Caption = 'LabeledEdit1'
    TabOrder = 8
    Text = ''
    Visible = False
  end
  object LabeledEdit2: TLabeledEdit
    Left = 904
    Top = 360
    Width = 121
    Height = 23
    EditLabel.Width = 67
    EditLabel.Height = 15
    EditLabel.Caption = 'LabeledEdit2'
    TabOrder = 9
    Text = ''
    Visible = False
  end
  object LabeledEditN: TLabeledEdit
    Left = 905
    Top = 264
    Width = 121
    Height = 23
    EditLabel.Width = 9
    EditLabel.Height = 15
    EditLabel.Caption = 'N'
    TabOrder = 10
    Text = ''
    Visible = False
  end
  object Memo1: TMemo
    Left = 624
    Top = 432
    Width = 265
    Height = 121
    TabOrder = 11
    Visible = False
  end
  object MainMenu1: TMainMenu
    Left = 696
    Top = 560
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
  end
  object OpenTextFileDialog1: TOpenTextFileDialog
    DefaultExt = 'txt'
    Left = 736
    Top = 560
  end
  object SaveTextFileDialog1: TSaveTextFileDialog
    DefaultExt = 'txt'
    Left = 776
    Top = 560
  end
  object ColorDialog1: TColorDialog
    Left = 816
    Top = 560
  end
end
