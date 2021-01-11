<?xml version="1.0"?>

<xsl:stylesheet version="2.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="/">
	<html>
		<body>
			<head>
				<meta charset="utf-8" />
				<title>Эталоны и маневры эталонов</title>
			</head>
			<b>Эталоны и маневры эталонов</b>
			<!--<br></br>
			<br></br>-->
			<i><xsl:apply-templates select="comment()"/></i>
			<br></br>
			<br></br>
			<xsl:apply-templates select="TObjectContr"/>
		</body>
	</html>
</xsl:template>

<xsl:template match="TObjectContr">
	<b>Эталоны</b>
	<br></br>
	<br></br>
	<table border="1" cellspacing="0">
		<!--<tr>
			<td><b><center>number</center></b></td>
			<td><b><center>ObjClass</center></b></td>
			<td><b><center>TO</center></b></td>
			<td><b><center>IO</center></b></td>
			<td><b><center>OGP</center></b></td>
			<td><b><center>tStart</center></b></td>
			<td><b><center>tFinish</center></b></td>
			<td><b><center>x</center></b></td>
			<td><b><center>y</center></b></td>
			<td><b><center>h</center></b></td>
			<td><b><center>psi</center></b></td>
			<td><b><center>v</center></b></td>
			<td><b><center>vh</center></b></td>
		</tr>-->
		<tr>
			<td><b><center>Номер<br></br>эталона</center></b></td>
			<td><b><center>Номер<br></br>категории</center></b></td>
			<td><b><center>Тип</center></b></td>
			<td><b><center>Индекс</center></b></td>
			<td><b><center>ОГП</center></b></td>
			<td><b><center>Время<br></br>начала<br></br>движения</center></b></td>
			<td><b><center>Время<br></br>окончания<br></br>движения</center></b></td>
			<td><b><center>X-координата</center></b></td>
			<td><b><center>Y-координата</center></b></td>
			<td><b><center>Высота</center></b></td>
			<td><b><center>Курс</center></b></td>
			<td><b><center>Скорость</center></b></td>
			<td><b><center>Скорость<br></br>изменения<br></br>высоты</center></b></td>
		</tr>
		<tr>
			<td><b><center></center></b></td>
			<td><b><center></center></b></td>
			<td><b><center></center></b></td>
			<td><b><center></center></b></td>
			<td><b><center></center></b></td>
			<td><b><center>с</center></b></td>
			<td><b><center>с</center></b></td>
			<td><b><center>м</center></b></td>
			<td><b><center>м</center></b></td>
			<td><b><center>м</center></b></td>
			<td><b><center>рад</center></b></td>
			<td><b><center>м/с</center></b></td>
			<td><b><center>м/с</center></b></td>
		</tr>
		<xsl:apply-templates select="ObjectContr"/>
	</table>

	<br></br>
	<br></br>

	<b>Маневры эталонов</b>
	<br></br>
	<br></br>
	<table border="1" cellspacing="0">
		<!--<tr>
			<td><b><center>tObjectContr_number</center></b></td>
			<td><b><center>number</center></b></td>
			<td><b><center>tStart</center></b></td>
			<td><b><center>tFinish</center></b></td>
			<td><b><center>a</center></b></td>
			<td><b><center>vh</center></b></td>
			<td><b><center>r</center></b></td>
		</tr>-->
		<tr>
			<td><b><center>Номер<br></br>эталона</center></b></td>
			<td><b><center>Номер<br></br>маневра</center></b></td>
			<td><b><center>Время<br></br>начала<br></br>маневра</center></b></td>
			<td><b><center>Время<br></br>окончания<br></br>маневра</center></b></td>
			<td><b><center>Ускорение</center></b></td>
			<td><b><center>Скорость<br></br>изменения<br></br>высоты</center></b></td>
			<td><b><center>Радиус<br></br>разворота</center></b></td>
		</tr>
		<tr>
			<td><b><center></center></b></td>
			<td><b><center></center></b></td>
			<td><b><center>с</center></b></td>
			<td><b><center>с</center></b></td>
			<td><b><center>м/с2</center></b></td>
			<td><b><center>м/с</center></b></td>
			<td><b><center>с</center></b></td>
		</tr>
		<xsl:apply-templates select="ObjectContr/Manevr"/>
	</table>
</xsl:template>

<xsl:template match="ObjectContr">
	<tr>
		<td><center><xsl:apply-templates select="@number"/></center></td>
		<td><center><xsl:apply-templates select="ObjClass"/></center></td>
		<td><center><xsl:apply-templates select="TO"/></center></td>
		<td><center><xsl:apply-templates select="IO"/></center></td>
		<td><center><xsl:apply-templates select="OGP"/></center></td>
		<td><center><xsl:apply-templates select="tStart"/></center></td>
		<td><center><xsl:apply-templates select="tFinish"/></center></td>
		<td><center><xsl:apply-templates select="x"/></center></td>
		<td><center><xsl:apply-templates select="y"/></center></td>
		<td><center><xsl:apply-templates select="h"/></center></td>
		<td><center><xsl:apply-templates select="psi"/></center></td>
		<td><center><xsl:apply-templates select="v"/></center></td>
		<td><center><xsl:apply-templates select="vh"/></center></td>
	</tr>
</xsl:template>

<xsl:template match="Manevr">
	<tr>
		<xsl:if test="@number = 1">
			<td>
				<xsl:attribute name="rowSpan">
					<xsl:value-of select="../count(Manevr)"/>
				</xsl:attribute>
				<center><xsl:apply-templates select="../@number"/></center>
			</td>
		</xsl:if>
		<td><center><xsl:apply-templates select="@number"/></center></td>
		<td><center><xsl:apply-templates select="tStart"/></center></td>
		<td><center><xsl:apply-templates select="tFinish"/></center></td>
		<td><center><xsl:apply-templates select="a"/></center></td>
		<td><center><xsl:apply-templates select="vh"/></center></td>
		<td><center><xsl:apply-templates select="r"/></center></td>
	</tr>
</xsl:template>

<xsl:template match="comment()">
	<xsl:value-of select="." />
</xsl:template>

</xsl:stylesheet>