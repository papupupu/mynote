# Generated by Django 2.2.12 on 2020-08-10 12:41

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('bookstore', '0006_book_is_active'),
    ]

    operations = [
        migrations.AlterModelOptions(
            name='book',
            options={'verbose_name': '图书', 'verbose_name_plural': '图书'},
        ),
        migrations.AlterField(
            model_name='book',
            name='pub',
            field=models.CharField(default='', max_length=100, verbose_name='出版社名称'),
        ),
    ]
