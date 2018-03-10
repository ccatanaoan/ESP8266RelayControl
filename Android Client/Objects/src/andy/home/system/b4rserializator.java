package andy.home.system;


import anywheresoftware.b4a.BA;
import anywheresoftware.b4a.B4AClass;
import anywheresoftware.b4a.BALayout;
import anywheresoftware.b4a.debug.*;

public class b4rserializator extends B4AClass.ImplB4AClass implements BA.SubDelegator{
    private static java.util.HashMap<String, java.lang.reflect.Method> htSubs;
    private void innerInitialize(BA _ba) throws Exception {
        if (ba == null) {
            ba = new BA(_ba, this, htSubs, "andy.home.system.b4rserializator");
            if (htSubs == null) {
                ba.loadHtSubs(this.getClass());
                htSubs = ba.htSubs;
            }
            
        }
        if (BA.isShellModeRuntimeCheck(ba)) 
			   this.getClass().getMethod("_class_globals", andy.home.system.b4rserializator.class).invoke(this, new Object[] {null});
        else
            ba.raiseEvent2(null, true, "class_globals", false);
    }

 public anywheresoftware.b4a.keywords.Common __c = null;
public int _t_uint_1 = 0;
public int _t_uint_2 = 0;
public int _t_uint_4 = 0;
public int _t_nint_1 = 0;
public int _t_nint_2 = 0;
public int _t_int_4 = 0;
public int _t_float_4 = 0;
public int _t_string = 0;
public int _t_long_bytes = 0;
public int _t_short_bytes = 0;
public int _t_small_uint = 0;
public byte _mark_begin = (byte)0;
public byte _mark_end = (byte)0;
public anywheresoftware.b4a.randomaccessfile.RandomAccessFile _raf = null;
public byte[] _smallbuffer = null;
public anywheresoftware.b4a.objects.streams.File.OutputStreamWrapper _out = null;
public andy.home.system.main _main = null;
public andy.home.system.starter _starter = null;
public String  _class_globals() throws Exception{
 //BA.debugLineNum = 3;BA.debugLine="Sub Class_Globals";
 //BA.debugLineNum = 4;BA.debugLine="Private const T_UINT_1 = 1, T_UINT_2 = 2, T_UINT_";
_t_uint_1 = (int) (1);
_t_uint_2 = (int) (2);
_t_uint_4 = (int) (3);
_t_nint_1 = (int) (4);
_t_nint_2 = (int) (5);
_t_int_4 = (int) (6);
_t_float_4 = (int) (7);
_t_string = (int) (8);
_t_long_bytes = (int) (9);
_t_short_bytes = (int) (0x40);
_t_small_uint = (int) (0x80);
 //BA.debugLineNum = 6;BA.debugLine="Private const MARK_BEGIN = 0x7E, MARK_END = 0x7F";
_mark_begin = (byte) (0x7e);
_mark_end = (byte) (0x7f);
 //BA.debugLineNum = 7;BA.debugLine="Private raf As RandomAccessFile";
_raf = new anywheresoftware.b4a.randomaccessfile.RandomAccessFile();
 //BA.debugLineNum = 8;BA.debugLine="Private smallbuffer(4) As Byte";
_smallbuffer = new byte[(int) (4)];
;
 //BA.debugLineNum = 9;BA.debugLine="Private out As OutputStream";
_out = new anywheresoftware.b4a.objects.streams.File.OutputStreamWrapper();
 //BA.debugLineNum = 10;BA.debugLine="End Sub";
return "";
}
public byte[]  _convertarraytobytes(Object[] _objects) throws Exception{
int _i = 0;
Object _o = null;
boolean _bool1 = false;
long _llng = 0L;
int _num = 0;
String _s = "";
byte[] _b = null;
 //BA.debugLineNum = 20;BA.debugLine="Public Sub ConvertArrayToBytes (Objects() As Objec";
 //BA.debugLineNum = 21;BA.debugLine="raf.Initialize3(smallbuffer, True)";
_raf.Initialize3(_smallbuffer,__c.True);
 //BA.debugLineNum = 22;BA.debugLine="Dim out As OutputStream";
_out = new anywheresoftware.b4a.objects.streams.File.OutputStreamWrapper();
 //BA.debugLineNum = 23;BA.debugLine="out.InitializeToBytesArray(0)";
_out.InitializeToBytesArray((int) (0));
 //BA.debugLineNum = 24;BA.debugLine="WriteByte(MARK_BEGIN)";
_writebyte(_mark_begin);
 //BA.debugLineNum = 25;BA.debugLine="WriteByte(Objects.Length)";
_writebyte((byte) (_objects.length));
 //BA.debugLineNum = 26;BA.debugLine="For i = 0 To Objects.Length - 1";
{
final int step6 = 1;
final int limit6 = (int) (_objects.length-1);
_i = (int) (0) ;
for (;(step6 > 0 && _i <= limit6) || (step6 < 0 && _i >= limit6) ;_i = ((int)(0 + _i + step6))  ) {
 //BA.debugLineNum = 27;BA.debugLine="Dim o As Object = Objects(i)";
_o = _objects[_i];
 //BA.debugLineNum = 29;BA.debugLine="If o Is Byte Then";
if (_o instanceof Byte) { 
 //BA.debugLineNum = 30;BA.debugLine="o = Bit.And(0xFF, o)";
_o = (Object)(__c.Bit.And((int) (0xff),(int)(BA.ObjectToNumber(_o))));
 }else if(_o instanceof Boolean) { 
 //BA.debugLineNum = 32;BA.debugLine="Dim bool1 As Boolean = o";
_bool1 = BA.ObjectToBoolean(_o);
 //BA.debugLineNum = 33;BA.debugLine="If bool1 Then o = 1 Else o = 0";
if (_bool1) { 
_o = (Object)(1);}
else {
_o = (Object)(0);};
 };
 //BA.debugLineNum = 35;BA.debugLine="If o Is Double Or o Is Float Then";
if (_o instanceof Double || _o instanceof Float) { 
 //BA.debugLineNum = 36;BA.debugLine="raf.WriteFloat(o, 0)";
_raf.WriteFloat((float)(BA.ObjectToNumber(_o)),(long) (0));
 //BA.debugLineNum = 37;BA.debugLine="WriteByte(T_FLOAT_4)";
_writebyte((byte) (_t_float_4));
 //BA.debugLineNum = 38;BA.debugLine="WriteRaf(4)";
_writeraf((int) (4));
 }else if(_o instanceof Long) { 
 //BA.debugLineNum = 40;BA.debugLine="WriteByte (T_UINT_4)";
_writebyte((byte) (_t_uint_4));
 //BA.debugLineNum = 41;BA.debugLine="Dim llng As Long = o";
_llng = BA.ObjectToLongNumber(_o);
 //BA.debugLineNum = 42;BA.debugLine="raf.WriteInt(llng, 0)";
_raf.WriteInt((int) (_llng),(long) (0));
 //BA.debugLineNum = 43;BA.debugLine="WriteRaf(4)";
_writeraf((int) (4));
 }else if(_o instanceof Integer || _o instanceof Short || _o instanceof Byte) { 
 //BA.debugLineNum = 45;BA.debugLine="Dim num As Int = o";
_num = (int)(BA.ObjectToNumber(_o));
 //BA.debugLineNum = 46;BA.debugLine="If Bit.And(T_SMALL_UINT - 1, num) = num Then";
if (__c.Bit.And((int) (_t_small_uint-1),_num)==_num) { 
 //BA.debugLineNum = 47;BA.debugLine="WriteByte (Bit.Or(T_SMALL_UINT, num))";
_writebyte((byte) (__c.Bit.Or(_t_small_uint,_num)));
 }else if(__c.Bit.And(_num,(int) (0xff))==_num) { 
 //BA.debugLineNum = 49;BA.debugLine="WriteByte (T_UINT_1)";
_writebyte((byte) (_t_uint_1));
 //BA.debugLineNum = 50;BA.debugLine="WriteByte (num)";
_writebyte((byte) (_num));
 }else if(__c.Bit.And(_num,(int) (0xffff))==_num) { 
 //BA.debugLineNum = 52;BA.debugLine="WriteByte (T_UINT_2)";
_writebyte((byte) (_t_uint_2));
 //BA.debugLineNum = 53;BA.debugLine="raf.WriteShort(num, 0)";
_raf.WriteShort((short) (_num),(long) (0));
 //BA.debugLineNum = 54;BA.debugLine="WriteRaf(2)";
_writeraf((int) (2));
 }else if(__c.Bit.And(_num,(int) (0xffffff00))==0xffffff00) { 
 //BA.debugLineNum = 56;BA.debugLine="WriteByte(T_NINT_1)";
_writebyte((byte) (_t_nint_1));
 //BA.debugLineNum = 57;BA.debugLine="WriteByte(num)";
_writebyte((byte) (_num));
 }else if(__c.Bit.And(_num,(int) (0xffff0000))==0xffff0000) { 
 //BA.debugLineNum = 59;BA.debugLine="WriteByte(T_NINT_2)";
_writebyte((byte) (_t_nint_2));
 //BA.debugLineNum = 60;BA.debugLine="raf.WriteShort(num, 0)";
_raf.WriteShort((short) (_num),(long) (0));
 //BA.debugLineNum = 61;BA.debugLine="WriteRaf(2)";
_writeraf((int) (2));
 }else {
 //BA.debugLineNum = 63;BA.debugLine="WriteByte(T_INT_4)";
_writebyte((byte) (_t_int_4));
 //BA.debugLineNum = 64;BA.debugLine="raf.WriteInt(num, 0)";
_raf.WriteInt(_num,(long) (0));
 //BA.debugLineNum = 65;BA.debugLine="WriteRaf(4)";
_writeraf((int) (4));
 };
 }else if(_o instanceof String) { 
 //BA.debugLineNum = 68;BA.debugLine="WriteByte(T_STRING)";
_writebyte((byte) (_t_string));
 //BA.debugLineNum = 69;BA.debugLine="Dim s As String = o";
_s = BA.ObjectToString(_o);
 //BA.debugLineNum = 70;BA.debugLine="Dim b() As Byte = s.GetBytes(\"UTF8\")";
_b = _s.getBytes("UTF8");
 //BA.debugLineNum = 71;BA.debugLine="out.WriteBytes(b, 0, b.Length)";
_out.WriteBytes(_b,(int) (0),_b.length);
 //BA.debugLineNum = 72;BA.debugLine="WriteByte(0)";
_writebyte((byte) (0));
 }else if((__c.IsDevTool("B4i") && (__c.GetType(_o)).equals("B4IArray")) || (__c.GetType(_o)).equals("[B")) { 
 //BA.debugLineNum = 74;BA.debugLine="Dim b() As Byte = o";
_b = (byte[])(_o);
 //BA.debugLineNum = 75;BA.debugLine="If b.Length < T_SHORT_BYTES Then";
if (_b.length<_t_short_bytes) { 
 //BA.debugLineNum = 76;BA.debugLine="WriteByte(Bit.Or(T_SHORT_BYTES, b.Length))";
_writebyte((byte) (__c.Bit.Or(_t_short_bytes,_b.length)));
 }else {
 //BA.debugLineNum = 78;BA.debugLine="WriteByte(T_LONG_BYTES)";
_writebyte((byte) (_t_long_bytes));
 //BA.debugLineNum = 79;BA.debugLine="raf.WriteShort(b.Length, 0)";
_raf.WriteShort((short) (_b.length),(long) (0));
 //BA.debugLineNum = 80;BA.debugLine="WriteRaf(2)";
_writeraf((int) (2));
 };
 //BA.debugLineNum = 82;BA.debugLine="out.WriteBytes(b, 0, b.Length)";
_out.WriteBytes(_b,(int) (0),_b.length);
 }else {
 //BA.debugLineNum = 84;BA.debugLine="Log($\"Invalid value: ${o}\"$)";
__c.Log(("Invalid value: "+__c.SmartStringFormatter("",_o)+""));
 };
 }
};
 //BA.debugLineNum = 87;BA.debugLine="WriteByte(MARK_END)";
_writebyte(_mark_end);
 //BA.debugLineNum = 88;BA.debugLine="Return out.ToBytesArray";
if (true) return _out.ToBytesArray();
 //BA.debugLineNum = 89;BA.debugLine="End Sub";
return null;
}
public Object[]  _convertbytestoarray(byte[] _bytes) throws Exception{
int _length = 0;
Object[] _result = null;
int _i = 0;
int _recordtype = 0;
Object _o = null;
long _lng = 0L;
int _b = 0;
byte[] _bb = null;
 //BA.debugLineNum = 101;BA.debugLine="Public Sub ConvertBytesToArray (Bytes() As Byte) A";
 //BA.debugLineNum = 102;BA.debugLine="If Bytes.Length = 0 Or Bytes(0) <> MARK_BEGIN Or";
if (_bytes.length==0 || _bytes[(int) (0)]!=_mark_begin || _bytes[(int) (_bytes.length-1)]!=_mark_end) { 
 //BA.debugLineNum = 103;BA.debugLine="Log(\"Invalid input!\")";
__c.Log("Invalid input!");
 //BA.debugLineNum = 104;BA.debugLine="Return Array()";
if (true) return new Object[]{};
 };
 //BA.debugLineNum = 106;BA.debugLine="raf.Initialize3(Bytes, True)";
_raf.Initialize3(_bytes,__c.True);
 //BA.debugLineNum = 107;BA.debugLine="raf.CurrentPosition = 1";
_raf.CurrentPosition = (long) (1);
 //BA.debugLineNum = 108;BA.debugLine="Dim length As Int = raf.ReadUnsignedByte(raf.Curr";
_length = _raf.ReadUnsignedByte(_raf.CurrentPosition);
 //BA.debugLineNum = 109;BA.debugLine="Dim result(length) As Object";
_result = new Object[_length];
{
int d0 = _result.length;
for (int i0 = 0;i0 < d0;i0++) {
_result[i0] = new Object();
}
}
;
 //BA.debugLineNum = 110;BA.debugLine="For i = 0 To length - 1";
{
final int step9 = 1;
final int limit9 = (int) (_length-1);
_i = (int) (0) ;
for (;(step9 > 0 && _i <= limit9) || (step9 < 0 && _i >= limit9) ;_i = ((int)(0 + _i + step9))  ) {
 //BA.debugLineNum = 111;BA.debugLine="Dim recordType As Int = raf.ReadUnsignedByte(raf";
_recordtype = _raf.ReadUnsignedByte(_raf.CurrentPosition);
 //BA.debugLineNum = 112;BA.debugLine="Dim o As Object";
_o = new Object();
 //BA.debugLineNum = 113;BA.debugLine="Select recordType";
switch (BA.switchObjectToInt(_recordtype,_t_uint_1,_t_uint_2,_t_uint_4,_t_int_4,_t_nint_1,_t_nint_2,_t_float_4,_t_string,_t_long_bytes)) {
case 0: {
 //BA.debugLineNum = 115;BA.debugLine="o = raf.ReadUnsignedByte(raf.CurrentPosition)";
_o = (Object)(_raf.ReadUnsignedByte(_raf.CurrentPosition));
 break; }
case 1: {
 //BA.debugLineNum = 117;BA.debugLine="o = Bit.And(0xFFFF, raf.ReadShort(raf.CurrentP";
_o = (Object)(__c.Bit.And((int) (0xffff),(int) (_raf.ReadShort(_raf.CurrentPosition))));
 break; }
case 2: {
 //BA.debugLineNum = 119;BA.debugLine="Dim lng As Long = raf.ReadInt(raf.CurrentPosit";
_lng = (long) (_raf.ReadInt(_raf.CurrentPosition));
 //BA.debugLineNum = 121;BA.debugLine="If lng < 0 Then lng = lng + 4294967296";
if (_lng<0) { 
_lng = (long) (_lng+4294967296L);};
 //BA.debugLineNum = 122;BA.debugLine="o = lng";
_o = (Object)(_lng);
 break; }
case 3: {
 //BA.debugLineNum = 124;BA.debugLine="o = raf.ReadInt(raf.CurrentPosition)";
_o = (Object)(_raf.ReadInt(_raf.CurrentPosition));
 break; }
case 4: {
 //BA.debugLineNum = 126;BA.debugLine="o = Bit.Or(0xFFFFFF00, raf.ReadSignedByte(raf.";
_o = (Object)(__c.Bit.Or((int) (0xffffff00),(int) (_raf.ReadSignedByte(_raf.CurrentPosition))));
 break; }
case 5: {
 //BA.debugLineNum = 128;BA.debugLine="o = Bit.Or(0xFFFF0000, raf.ReadShort(raf.Curre";
_o = (Object)(__c.Bit.Or((int) (0xffff0000),(int) (_raf.ReadShort(_raf.CurrentPosition))));
 break; }
case 6: {
 //BA.debugLineNum = 130;BA.debugLine="o = raf.ReadFloat(raf.CurrentPosition)";
_o = (Object)(_raf.ReadFloat(_raf.CurrentPosition));
 break; }
case 7: {
 //BA.debugLineNum = 132;BA.debugLine="For b = raf.CurrentPosition To Bytes.Length -";
{
final int step30 = 1;
final int limit30 = (int) (_bytes.length-1);
_b = (int) (_raf.CurrentPosition) ;
for (;(step30 > 0 && _b <= limit30) || (step30 < 0 && _b >= limit30) ;_b = ((int)(0 + _b + step30))  ) {
 //BA.debugLineNum = 133;BA.debugLine="If Bytes(b) = 0 Then Exit";
if (_bytes[_b]==0) { 
if (true) break;};
 }
};
 //BA.debugLineNum = 135;BA.debugLine="o = BytesToString(Bytes, raf.CurrentPosition,";
_o = (Object)(__c.BytesToString(_bytes,(int) (_raf.CurrentPosition),(int) (_b-_raf.CurrentPosition),"utf8"));
 //BA.debugLineNum = 136;BA.debugLine="raf.CurrentPosition = b + 1";
_raf.CurrentPosition = (long) (_b+1);
 break; }
case 8: {
 //BA.debugLineNum = 138;BA.debugLine="Dim bb(Bit.And(0xFFFF, raf.ReadShort(raf.Curre";
_bb = new byte[__c.Bit.And((int) (0xffff),(int) (_raf.ReadShort(_raf.CurrentPosition)))];
;
 //BA.debugLineNum = 139;BA.debugLine="raf.ReadBytes(bb, 0, bb.Length, raf.CurrentPos";
_raf.ReadBytes(_bb,(int) (0),_bb.length,_raf.CurrentPosition);
 //BA.debugLineNum = 140;BA.debugLine="o = bb";
_o = (Object)(_bb);
 break; }
default: {
 //BA.debugLineNum = 142;BA.debugLine="If Bit.And(recordType, T_SMALL_UINT) = T_SMALL";
if (__c.Bit.And(_recordtype,_t_small_uint)==_t_small_uint) { 
 //BA.debugLineNum = 143;BA.debugLine="o = Bit.And(recordType, T_SMALL_UINT - 1)";
_o = (Object)(__c.Bit.And(_recordtype,(int) (_t_small_uint-1)));
 }else if(__c.Bit.And(_recordtype,_t_short_bytes)==_t_short_bytes) { 
 //BA.debugLineNum = 145;BA.debugLine="Dim bb (Bit.And(recordType, T_SHORT_BYTES - 1";
_bb = new byte[__c.Bit.And(_recordtype,(int) (_t_short_bytes-1))];
;
 //BA.debugLineNum = 146;BA.debugLine="raf.ReadBytes(bb, 0, bb.Length, raf.CurrentPo";
_raf.ReadBytes(_bb,(int) (0),_bb.length,_raf.CurrentPosition);
 //BA.debugLineNum = 147;BA.debugLine="o = bb";
_o = (Object)(_bb);
 }else {
 //BA.debugLineNum = 149;BA.debugLine="Log(\"Invalid field: \" & recordType)";
__c.Log("Invalid field: "+BA.NumberToString(_recordtype));
 };
 break; }
}
;
 //BA.debugLineNum = 152;BA.debugLine="result(i) = o";
_result[_i] = _o;
 }
};
 //BA.debugLineNum = 154;BA.debugLine="Return result";
if (true) return _result;
 //BA.debugLineNum = 155;BA.debugLine="End Sub";
return null;
}
public String  _initialize(anywheresoftware.b4a.BA _ba) throws Exception{
innerInitialize(_ba);
 //BA.debugLineNum = 12;BA.debugLine="Public Sub Initialize";
 //BA.debugLineNum = 14;BA.debugLine="End Sub";
return "";
}
public String  _writebyte(byte _b) throws Exception{
 //BA.debugLineNum = 91;BA.debugLine="Private Sub WriteByte(b As Byte)";
 //BA.debugLineNum = 92;BA.debugLine="out.WriteBytes(Array As Byte(b), 0, 1)";
_out.WriteBytes(new byte[]{_b},(int) (0),(int) (1));
 //BA.debugLineNum = 93;BA.debugLine="End Sub";
return "";
}
public String  _writeraf(int _length) throws Exception{
 //BA.debugLineNum = 95;BA.debugLine="Private Sub WriteRaf (Length As Int)";
 //BA.debugLineNum = 96;BA.debugLine="out.WriteBytes(smallbuffer, 0, Length)";
_out.WriteBytes(_smallbuffer,(int) (0),_length);
 //BA.debugLineNum = 97;BA.debugLine="End Sub";
return "";
}
public Object callSub(String sub, Object sender, Object[] args) throws Exception {
BA.senderHolder.set(sender);
return BA.SubDelegator.SubNotFound;
}
}
