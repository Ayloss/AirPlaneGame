<GameFile>
  <PropertyGroup Name="ControlLayer" Type="Layer" ID="43e4ddb2-a67b-4fb4-a4c6-0869e37311cf" Version="3.10.0.0" />
  <Content ctype="GameProjectContent">
    <Content>
      <Animation Duration="0" Speed="1.0000" />
      <ObjectData Name="Layer" Tag="30" ctype="GameLayerObjectData">
        <Size X="480.0000" Y="800.0000" />
        <Children>
          <AbstractNodeData Name="gameControl" ActionTag="6270368" Tag="31" IconVisible="False" RightMargin="420.0000" TopMargin="7.5000" BottomMargin="747.5000" TouchEnable="True" StretchWidthEnable="True" FontSize="14" Scale9Enable="True" LeftEage="15" RightEage="15" TopEage="11" BottomEage="11" Scale9OriginX="15" Scale9OriginY="11" Scale9Width="30" Scale9Height="23" ShadowOffsetX="2.0000" ShadowOffsetY="-2.0000" ctype="ButtonObjectData">
            <Size X="60.0000" Y="45.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="30.0000" Y="770.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0625" Y="0.9625" />
            <PreSize X="0.1250" Y="0.0562" />
            <TextColor A="255" R="65" G="65" B="70" />
            <DisabledFileData Type="Default" Path="Default/Button_Disable.png" Plist="" />
            <PressedFileData Type="Normal" Path="ui/shoot/game_pause_pressed.png" Plist="" />
            <NormalFileData Type="Normal" Path="ui/shoot/game_pause_nor.png" Plist="" />
            <OutlineColor A="255" R="255" G="0" B="0" />
            <ShadowColor A="255" R="110" G="110" B="110" />
          </AbstractNodeData>
          <AbstractNodeData Name="score" ActionTag="580259843" Tag="32" IconVisible="False" LeftMargin="60.0000" RightMargin="392.0000" TopMargin="19.0000" BottomMargin="755.0000" LabelText="0" ctype="TextBMFontObjectData">
            <Size X="28.0000" Y="26.0000" />
            <AnchorPoint />
            <Position X="60.0000" Y="755.0000" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="127" G="127" B="127" />
            <PrePosition X="0.1250" Y="0.9438" />
            <PreSize X="0.0583" Y="0.0325" />
            <LabelBMFontFile_CNB Type="Normal" Path="font/font.fnt" Plist="" />
          </AbstractNodeData>
          <AbstractNodeData Name="bombIcon" ActionTag="1737880133" Tag="4" IconVisible="False" LeftMargin="3.3754" RightMargin="413.6246" TopMargin="739.8245" BottomMargin="3.1755" ctype="SpriteObjectData">
            <Size X="63.0000" Y="57.0000" />
            <AnchorPoint ScaleX="0.5000" ScaleY="0.5000" />
            <Position X="34.8754" Y="31.6755" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="255" G="255" B="255" />
            <PrePosition X="0.0727" Y="0.0396" />
            <PreSize X="0.1312" Y="0.0712" />
            <FileData Type="Normal" Path="ui/shoot/bomb.png" Plist="" />
            <BlendFunc Src="1" Dst="771" />
          </AbstractNodeData>
          <AbstractNodeData Name="bombNum" ActionTag="-889263369" Tag="5" IconVisible="False" LeftMargin="66.0789" RightMargin="355.9211" TopMargin="758.7093" BottomMargin="15.2907" LabelText="X0" ctype="TextBMFontObjectData">
            <Size X="58.0000" Y="26.0000" />
            <AnchorPoint ScaleY="0.5000" />
            <Position X="66.0789" Y="28.2907" />
            <Scale ScaleX="1.0000" ScaleY="1.0000" />
            <CColor A="255" R="127" G="127" B="127" />
            <PrePosition X="0.1377" Y="0.0354" />
            <PreSize X="0.1208" Y="0.0325" />
            <LabelBMFontFile_CNB Type="Normal" Path="font/font.fnt" Plist="" />
          </AbstractNodeData>
        </Children>
      </ObjectData>
    </Content>
  </Content>
</GameFile>