<?xml version="1.0"?>

<xsl:stylesheet version="2.0"
xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

<xsl:template match="comment()">
	<b><i><xsl:value-of select="." /></i></b>
</xsl:template>

<xsl:template match="TObjectContr">
	<html>
		<head>
			<meta charset="utf-8" />
			<title>Тег META, атрибут charset</title>
		</head>
		<body>
    			<h2>ObjectContr</h2>
    			<table border="1" cellspacing="0">
      				<tr>
						<td><b><center>number</center></b></td>
						<td><b><center>tStart</center></b></td>
						<td><b><center>tFinish</center></b></td>
						<td><b><center>tAttack</center></b></td>
						<td><b><center>tInterval<br>Attack</br></center></b></td>
						<td><b><center>x</center></b></td>
						<td><b><center>y</center></b></td>
						<td><b><center>h</center></b></td>
						<td><b><center>psi</center></b></td>
						<td><b><center>v</center></b></td>
						<td><b><center>vh</center></b></td>
						<td><b><center>distance</center></b></td>
						<td><b><center>numPozRegion</center></b></td>
						<td><b><center>countManevr</center></b></td>
						<td><b><center>OGP</center></b></td>
						<td><b><center>IVO</center></b></td>
						<td><b><center>TVO</center></b></td>
						<td><b><center>countKR</center></b></td>
						<td><b><center>TKR</center></b></td>
						<td><b><center>trackBz</center></b></td>
						<td><b><center>imitObj</center></b></td>
						<td><b><center>trsChar</center></b></td>
						<td><b><center>trackImit</center></b></td>
      				</tr>
<!--
      				<tr>
						<td><b><center>Номер</center></b></td>
						<td><b><center>Время начала движения</center></b></td>
						<td><b><center>Время окончания движения</center></b></td>
						<td><b><center>Время атаки</center></b></td>
						<td><b><center>Интервал атаки</center></b></td>
						<td><b><center>X-координата</center></b></td>
						<td><b><center>Y-координата</center></b></td>
						<td><b><center>Высота</center></b></td>
						<td><b><center>Угол</center></b></td>
						<td><b><center>Скорость</center></b></td>
						<td><b><center>Скорость изменения высоты</center></b></td>
						<td><b><center>Дистанция</center></b></td>
						<td><b><center>Номер позиционного района</center></b></td>
						<td><b><center>Количество маневров</center></b></td>
						<td><b><center>ОГП</center></b></td>
						<td><b><center>ИВО</center></b></td>
						<td><b><center>ТВО</center></b></td>
						<td><b><center>Количество КР</center></b></td>
						<td><b><center>Тип КР</center></b></td>
						<td><b><center>Признак занятости формуляра</center></b></td>
						<td><b><center>Признак имитационного объекта</center></b></td>
						<td><b><center>Тип трассы</center></b></td>
						<td><b><center>Признак включения трассы в имитацию</center></b></td>
      				</tr>
-->
      				<tr>
						<td><b><center></center></b></td>
						<td><b><center>с</center></b></td>
						<td><b><center>с</center></b></td>
						<td><b><center>с</center></b></td>
						<td><b><center>с</center></b></td>
						<td><b><center>м</center></b></td>
						<td><b><center>м</center></b></td>
						<td><b><center>м</center></b></td>
						<td><b><center>рад</center></b></td>
						<td><b><center>м/с</center></b></td>
						<td><b><center>м/с2</center></b></td>
						<td><b><center>м</center></b></td>
						<td><b><center></center></b></td>
						<td><b><center></center></b></td>
						<td><b><center></center></b></td>
						<td><b><center></center></b></td>
						<td><b><center></center></b></td>
						<td><b><center></center></b></td>
						<td><b><center></center></b></td>
						<td><b><center></center></b></td>
						<td><b><center></center></b></td>
						<td><b><center></center></b></td>
						<td><b><center></center></b></td>
      				</tr>
				<xsl:apply-templates select="ObjectContr"/>
    			</table>
				
    			<h2>Manevr</h2>
    			<table border="1" cellspacing="0">
      				<tr>
						<td><b><center>tObjectContr_number</center></b></td>
						<td><b><center>number</center></b></td>
						<td><b><center>tStart</center></b></td>
						<td><b><center>tFinish</center></b></td>
						<td><b><center>a</center></b></td>
						<td><b><center>vh</center></b></td>
						<td><b><center>r</center></b></td>
      				</tr>
      				<tr>
						<td><b><center>Номер КЗ</center></b></td>
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
				<xsl:apply-templates select="ObjectContr/Manevr"/>
    			</table>
				
		</body>
	</html>
</xsl:template>

<xsl:template match="ObjectContr">
	<tr>
		<td><center><xsl:apply-templates select="@number"/></center></td>
		<td><center><xsl:apply-templates select="tStart"/></center></td>
		<td><center><xsl:apply-templates select="tFinish"/></center></td>
		<td><center><xsl:apply-templates select="tAttack"/></center></td>
		<td><center><xsl:apply-templates select="tIntervalAttack"/></center></td>
		<td><center><xsl:apply-templates select="x"/></center></td>
		<td><center><xsl:apply-templates select="y"/></center></td>
		<td><center><xsl:apply-templates select="h"/></center></td>
		<td><center><xsl:apply-templates select="psi"/></center></td>
		<td><center><xsl:apply-templates select="v"/></center></td>
		<td><center><xsl:apply-templates select="vh"/></center></td>
		<td><center><xsl:apply-templates select="distance"/></center></td>
		<td><center><xsl:apply-templates select="numPozRegion"/></center></td>
		<td><center><xsl:apply-templates select="countManevr"/></center></td>
		<td><center><xsl:apply-templates select="OGP"/></center></td>
		<td><center><xsl:apply-templates select="IVO"/></center></td>
		<td><center><xsl:apply-templates select="TVO"/></center></td>
		<td><center><xsl:apply-templates select="countKR"/></center></td>
		<td><center><xsl:apply-templates select="TKR"/></center></td>
		<td><center><xsl:apply-templates select="trackBz"/></center></td>
		<td><center><xsl:apply-templates select="imitObj"/></center></td>
		<td><center><xsl:apply-templates select="trsChar"/></center></td>
		<td><center><xsl:apply-templates select="trackImit"/></center></td>
	</tr>
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

