#include "B4RDefines.h"

B4R::Array* b4r_globalstore::_globalbuffer;
B4R::ByteConverter* b4r_globalstore::_bc;
UInt b4r_globalstore::_mmsrcoffset;
UInt b4r_globalstore::_mmdestoffset;
UInt b4r_globalstore::_mmcount;
B4R::Array* b4r_globalstore::_slot0;
B4R::Array* b4r_globalstore::_slot1;
B4R::Array* b4r_globalstore::_slot2;
B4R::Array* b4r_globalstore::_slot3;
B4R::Array* b4r_globalstore::_slot4;
B4R::Array* b4r_globalstore::_slots;
B4R::Array* b4r_globalstore::_lengths;
b4r_main* b4r_globalstore::_main;
b4r_wifiserver* b4r_globalstore::_wifiserver;
static Byte be_gann1_4e1[100];
static B4R::Array be_gann1_4e2;
static B4R::ByteConverter be_gann2_3;
static Byte be_gann4_4e1[0];
static B4R::Array be_gann4_4e2;
static Byte be_gann4_11e1[0];
static B4R::Array be_gann4_11e2;
static Byte be_gann4_18e1[0];
static B4R::Array be_gann4_18e2;
static Byte be_gann4_25e1[0];
static B4R::Array be_gann4_25e2;
static Byte be_gann4_32e1[0];
static B4R::Array be_gann4_32e2;
static B4R::Object be_gann5_10;
static B4R::Object be_gann5_12;
static B4R::Object be_gann5_14;
static B4R::Object be_gann5_16;
static B4R::Object be_gann5_18;
static B4R::Object* be_gann5_19e1[5];
static B4R::Array be_gann5_19e2;
static Byte be_gann6_4e1[5];
static B4R::Array be_gann6_4e2;


 void SetSlot(B4R::Object* o) {
	B4R::ArrayByte* ab = b4r_globalstore::_globalbuffer;
	B4R::ArrayByte* arr = (B4R::ArrayByte*)B4R::Object::toPointer(o);
	arr->data = (Byte*)ab->data + b4r_globalstore::_mmsrcoffset;
	arr->length = b4r_globalstore::_mmcount;
}
void MemMove(B4R::Object* o) {
	B4R::ArrayByte* ab = b4r_globalstore::_globalbuffer;
	memmove((Byte*)ab->data + b4r_globalstore::_mmdestoffset, 
		(Byte*)ab->data + b4r_globalstore::_mmsrcoffset, b4r_globalstore::_mmcount);
}
void b4r_globalstore::_process_globals(){
const UInt cp = B4R::StackMemory::cp;
 //BA.debugLineNum = 3;BA.debugLine="Sub Process_Globals";
 //BA.debugLineNum = 6;BA.debugLine="Private GlobalBuffer(100) As Byte";
b4r_globalstore::_globalbuffer =be_gann1_4e2.wrap(be_gann1_4e1,100);
 //BA.debugLineNum = 7;BA.debugLine="Private bc As ByteConverter";
b4r_globalstore::_bc = &be_gann2_3;
 //BA.debugLineNum = 8;BA.debugLine="Private mmSrcOffset, mmDestOffset, mmCount As UIn";
b4r_globalstore::_mmsrcoffset = 0;
b4r_globalstore::_mmdestoffset = 0;
b4r_globalstore::_mmcount = 0;
 //BA.debugLineNum = 10;BA.debugLine="Public Slot0(), Slot1(), Slot2(), Slot3(), Slot4(";
b4r_globalstore::_slot0 =be_gann4_4e2.wrap(be_gann4_4e1,0);
b4r_globalstore::_slot1 =be_gann4_11e2.wrap(be_gann4_11e1,0);
b4r_globalstore::_slot2 =be_gann4_18e2.wrap(be_gann4_18e1,0);
b4r_globalstore::_slot3 =be_gann4_25e2.wrap(be_gann4_25e1,0);
b4r_globalstore::_slot4 =be_gann4_32e2.wrap(be_gann4_32e1,0);
 //BA.debugLineNum = 11;BA.debugLine="Private slots() As Object = Array(Slot0, Slot1, S";
b4r_globalstore::_slots = be_gann5_19e2.create(be_gann5_19e1,5,100,be_gann5_10.wrapPointer(b4r_globalstore::_slot0),be_gann5_12.wrapPointer(b4r_globalstore::_slot1),be_gann5_14.wrapPointer(b4r_globalstore::_slot2),be_gann5_16.wrapPointer(b4r_globalstore::_slot3),be_gann5_18.wrapPointer(b4r_globalstore::_slot4));
 //BA.debugLineNum = 12;BA.debugLine="Private lengths(5) As Byte";
b4r_globalstore::_lengths =be_gann6_4e2.wrap(be_gann6_4e1,5);
 //BA.debugLineNum = 13;BA.debugLine="End Sub";
}
void b4r_globalstore::_put(Int _slot,B4R::Array* _value){
const UInt cp = B4R::StackMemory::cp;
Int _index = 0;
Int _i = 0;
Int _tocopy = 0;
Byte _b = 0;
 //BA.debugLineNum = 15;BA.debugLine="Public Sub Put(slot As Int, Value() As Byte)";
 //BA.debugLineNum = 16;BA.debugLine="Dim index As Int = 0";
_index = 0;
 //BA.debugLineNum = 17;BA.debugLine="For i = 0 To slot - 1";
{
const int step2 = 1;
const int limit2 = (Int) (_slot-1);
_i = 0 ;
for (;(step2 > 0 && _i <= limit2) || (step2 < 0 && _i >= limit2) ;_i = ((Int)(0 + _i + step2))  ) {
 //BA.debugLineNum = 18;BA.debugLine="index = index + lengths(i)";
_index = (Int) (_index+((Byte*)b4r_globalstore::_lengths->getData((UInt) (_i)))[B4R::Array::staticIndex]);
 }
};
 //BA.debugLineNum = 20;BA.debugLine="Dim ToCopy As Int = 0";
_tocopy = 0;
 //BA.debugLineNum = 21;BA.debugLine="For i = slot + 1 To lengths.Length - 1";
{
const int step6 = 1;
const int limit6 = (Int) (b4r_globalstore::_lengths->length-1);
_i = (Int) (_slot+1) ;
for (;(step6 > 0 && _i <= limit6) || (step6 < 0 && _i >= limit6) ;_i = ((Int)(0 + _i + step6))  ) {
 //BA.debugLineNum = 22;BA.debugLine="ToCopy = ToCopy + lengths(i)";
_tocopy = (Int) (_tocopy+((Byte*)b4r_globalstore::_lengths->getData((UInt) (_i)))[B4R::Array::staticIndex]);
 }
};
 //BA.debugLineNum = 24;BA.debugLine="If lengths(slot) <> Value.Length Then";
if (((Byte*)b4r_globalstore::_lengths->getData((UInt) (_slot)))[B4R::Array::staticIndex]!=_value->length) { 
 //BA.debugLineNum = 25;BA.debugLine="mmSrcOffset = index + lengths(slot)";
b4r_globalstore::_mmsrcoffset = (UInt) (_index+((Byte*)b4r_globalstore::_lengths->getData((UInt) (_slot)))[B4R::Array::staticIndex]);
 //BA.debugLineNum = 26;BA.debugLine="mmDestOffset = index + Value.Length";
b4r_globalstore::_mmdestoffset = (UInt) (_index+_value->length);
 //BA.debugLineNum = 27;BA.debugLine="mmCount = ToCopy";
b4r_globalstore::_mmcount = (UInt) (_tocopy);
 //BA.debugLineNum = 28;BA.debugLine="RunNative(\"MemMove\", Null)";
Common_RunNative(MemMove,Common_Null);
 };
 //BA.debugLineNum = 30;BA.debugLine="Dim b As Byte = GlobalBuffer(index + Value.Length";
_b = ((Byte*)b4r_globalstore::_globalbuffer->getData((UInt) (_index+_value->length+_tocopy-1)))[B4R::Array::staticIndex];
 //BA.debugLineNum = 31;BA.debugLine="bc.ArrayCopy2(Value, 0, GlobalBuffer, index, Valu";
b4r_globalstore::_bc->ArrayCopy2(_value,(UInt) (0),b4r_globalstore::_globalbuffer,(UInt) (_index),(UInt) (_value->length));
 //BA.debugLineNum = 32;BA.debugLine="lengths(slot) = Value.Length";
((Byte*)b4r_globalstore::_lengths->getData((UInt) (_slot)))[B4R::Array::staticIndex] = (Byte) (_value->length);
 //BA.debugLineNum = 33;BA.debugLine="mmSrcOffset = 0";
b4r_globalstore::_mmsrcoffset = (UInt) (0);
 //BA.debugLineNum = 34;BA.debugLine="For index = 0 To slots.Length - 1";
{
const int step19 = 1;
const int limit19 = (Int) (b4r_globalstore::_slots->length-1);
_index = 0 ;
for (;(step19 > 0 && _index <= limit19) || (step19 < 0 && _index >= limit19) ;_index = ((Int)(0 + _index + step19))  ) {
 //BA.debugLineNum = 35;BA.debugLine="If index > 0 Then mmSrcOffset = mmSrcOffset + le";
if (_index>0) { 
b4r_globalstore::_mmsrcoffset = (UInt) (b4r_globalstore::_mmsrcoffset+((Byte*)b4r_globalstore::_lengths->getData((UInt) (_index-1)))[B4R::Array::staticIndex]);};
 //BA.debugLineNum = 36;BA.debugLine="mmCount = lengths(index)";
b4r_globalstore::_mmcount = (UInt) (((Byte*)b4r_globalstore::_lengths->getData((UInt) (_index)))[B4R::Array::staticIndex]);
 //BA.debugLineNum = 37;BA.debugLine="RunNative(\"SetSlot\", slots(index))";
Common_RunNative(SetSlot,((B4R::Object**)b4r_globalstore::_slots->getData((UInt) (_index)))[B4R::Array::staticIndex]);
 }
};
 //BA.debugLineNum = 39;BA.debugLine="End Sub";
B4R::StackMemory::cp = cp;
}
