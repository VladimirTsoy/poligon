<?xml version="1.0"?>

<xsl:stylesheet version="2.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="TKRManevr">
	<html>
		<head>
			<meta charset="utf-8" />
			<title>Тег META, атрибут charset</title>
		</head>
		<body>
    			<h2>KRManevr</h2>
    			<table border="1" cellspacing="0">
      				<tr>
						<td><b><center>Number KR</center></b></td>
						<td><b><center>Number Manevr</center></b></td>
						<td><b><center>tStart</center></b></td>
						<td><b><center>tFinish</center></b></td>
						<td><b><center>a</center></b></td>
						<td><b><center>vh</center></b></td>
						<td><b><center>r</center></b></td>
      				</tr>
      				<tr>
						<td><b><center>Номер КР</center></b></td>
						<td><b><center>Номер маневра</center></b></td>
						<td><b><center>Время начала</center></b></td>
						<td><b><center>Время окончания</center></b></td>
						<td><b><center>Ускорение</center></b></td>
						<td><b><center>Скорость изменения высоты</center></b></td>
						<td><b><center>Радиус</center></b></td>
      				</tr>
      				<tr>
						<td><b><center></center></b></td>
						<td><b><center></center></b></td>
						<td><b><center>с</center></b></td>
						<td><b><center>с</center></b></td>
						<td><b><center>м/с2</center></b></td>
						<td><b><center>м/с2</center></b></td>
						<td><b><center>м</center></b></td>
      				</tr>
				<xsl:apply-templates select="KRManevr"/>
    			</table>
		</body>
	</html>
</xsl:template>

<xsl:template match="KRManevr">
		<xsl:apply-templates select="Manevr"/>
</xsl:template>

<xsl:template match="Manevr">
	<tr>
		<td><center><xsl:apply-templates select="../@number"/></center></td>
		<td><center><xsl:apply-templates select="@number"/></center></td>
		<td><center><xsl:apply-templates select="tStart"/></center></td>
		<td><center><xsl:apply-templates select="tFinish"/></center></td>
		<td><center><xsl:apply-templates select="a"/></center></td>
		<td><center><xsl:apply-templates select="vh"/></center></td>
		<td><center><xsl:apply-templates select="r"/></center></td>
	</tr>
</xsl:template>

</xsl:stylesheet> 

