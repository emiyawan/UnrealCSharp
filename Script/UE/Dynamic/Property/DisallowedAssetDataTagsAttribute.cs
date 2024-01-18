using System;
using Script.Common;
namespace Script.Dynamic
{
    [AttributeUsage(AttributeTargets.Property)]
    public class DisallowedAssetDataTagsAttribute : Attribute
    {
    public string MetaValue { get; set; }
    public DisallowedAssetDataTagsAttribute(string MetaValue)
    {
        this.MetaValue = MetaValue;
    }
    public DisallowedAssetDataTagsAttribute()
    {
        this.MetaValue = "true";
    }
    }
}