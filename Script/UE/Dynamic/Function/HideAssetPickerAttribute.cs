using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Method)]
    public class HideAssetPickerAttribute : Attribute
    {
    private string MetaValue;
    public string DisplayValue
    {
        get { return MetaValue; }
        set { MetaValue = value; }
    }
    public HideAssetPickerAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    }
}