object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 588
  ClientWidth = 1049
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -12
  Font.Name = 'Segoe UI'
  Font.Style = []
  TextHeight = 15
  object Image1: TImage
    Left = 8
    Top = 8
    Width = 881
    Height = 545
    OnClick = Image1Click
    OnMouseDown = Image1MouseDown
  end
  object Button1: TButton
    Left = 895
    Top = 8
    Width = 154
    Height = 73
    Caption = 'Button1'
    TabOrder = 0
  end
  object ComboBox1: TComboBox
    Left = 905
    Top = 101
    Width = 136
    Height = 23
    ItemIndex = 1
    TabOrder = 1
    Text = #1069#1083#1080#1087#1089
    Items.Strings = (
      #1053#1080#1095#1077#1075#1086
      #1069#1083#1080#1087#1089)
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
  object LabeledEdit5: TLabeledEdit
    Left = 905
    Top = 264
    Width = 121
    Height = 23
    EditLabel.Width = 9
    EditLabel.Height = 15
    EditLabel.Caption = 'N'
    TabOrder = 10
    Text = ''
  end
end
